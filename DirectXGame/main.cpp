#include "Audio.h"
#include "AxisIndicator.h"
#include "ClearScene.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "OverScene.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "TitleScene.h"
#include "WinApp.h"
enum class Scene {
	kUnkown = 0,

	kTitle,
	kGame,
	kClear,
	kOver
};

Scene scene = Scene::kUnkown;
TitleScene* titleScene = nullptr;
GameScene* gameScene = nullptr;
ClearScene* clearScene = nullptr;
OverScene* overScene = nullptr;

Model* model_ = nullptr;
WorldTransform* wolrldTransform_ = {};
ViewProjection* viewProjection_ = {};
MapChipField* mapChipField_ = nullptr;

// キー入力結果を受け取る箱
char keys[256] = {0};
char preKeys[256] = {0};

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧Sceneの解放
			delete titleScene;
			titleScene = nullptr;
			// 新Sceneの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished() && !gameScene->IsPlayerAlive()) {
			// シーン変更
			scene = Scene::kOver;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			overScene = new OverScene();
			overScene->Initalize();
		} else if (gameScene->IsClearF_() && gameScene->IsPlayerAlive()) {
			// シーン変更
			scene = Scene::kClear;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新シーンの生成と初期化
			clearScene = new ClearScene();
			clearScene->Initalize();
		}
		break;
	case Scene::kClear:
		if (clearScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧Sceneの解放
			delete clearScene;
			clearScene = nullptr;
			// 新Sceneの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initalize();
		}
		break;
	case Scene::kOver:
		if (overScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧Sceneの解放
			delete overScene;
			overScene = nullptr;
			// 新Sceneの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initalize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kClear:
		clearScene->Update();
		break;
	case Scene::kOver:
		overScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kClear:
		clearScene->Draw();
		break;
	case Scene::kOver:
		overScene->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	// GameScene* gameScene = nullptr;
	// TitleScene* titleScene = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	scene = Scene::kTitle;

	titleScene = new TitleScene;
	titleScene->Initalize();

	clearScene = new ClearScene;
	clearScene->Initalize();

	overScene = new OverScene;
	overScene->Initalize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		////タイトルシーンの毎フレーム処理
		// titleScene->Update();
		// シーンの切り替え
		ChangeScene();
		// 現在のシーン更新
		UpdateScene();
		// ゲームシーンの毎フレーム処理
		// gameScene->Update();
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		////タイトルシーンの描画
		// titleScene->Draw();
		DrawScene();
		// ゲームシーンの描画
		// gameScene->Draw();
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete gameScene;
	delete titleScene;
	delete overScene;
	delete clearScene;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}
