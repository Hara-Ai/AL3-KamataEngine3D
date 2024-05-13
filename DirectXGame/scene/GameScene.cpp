#include "GameScene.h"
#include "TextureManager.h"
#include "Player.h"
#include "WorldTransform.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete blockModel_;
	delete (block_);
	delete debugCamera_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldformBlock : worldTransformBlockLine) {
			delete worldformBlock;
		}
	}

	worldTransformBlocks_.clear();
	
}

	void GameScene::Initialize() {

		dxCommon_ = DirectXCommon::GetInstance();
		input_ = Input::GetInstance();
		audio_ = Audio::GetInstance();

		tetureHandle_ = TextureManager::Load("sample.png");

		// 3Dモデルの生成
		model_ = Model::Create();

		worldTransform_.Initialize();
		ViewProjection_.Initialize();

		// 自キャラの生成
		player_ = new Player();
		// 自キャラの初期化
		player_->Initialize(model_, tetureHandle_, &ViewProjection_);

		blockModel_ = Model::Create();

		block_ = Model();
		blockTextureHandle_ = TextureManager::Load("cube/cube.jpg");

		// 要素数
		const uint32_t kNumBlockVirtical = 10;
		const uint32_t kNumBlockHorizontal = 20;

		// ブロック1個分の横幅
		const float kBockWidth = 2.0f;
		const float kBockHeight = 2.0f;
		// 要素数を変更する
		worldTransformBlocks_.resize(kNumBlockHorizontal);

		// キューブの生成
		for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
			for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {

				worldTransformBlocks_[i][j] = new WorldTransform();
				worldTransformBlocks_[i][j]->Initialize();
				worldTransformBlocks_[i][j]->translation_.x = kBockWidth * i;
				worldTransformBlocks_[i][j]->translation_.y = kBockHeight * j;
			}
		}

		worldTransformBlocks_.resize(kNumBlockHorizontal);
		for (uint32_t i = 0; i < kNumBlockHorizontal; i++) {
			worldTransformBlocks_[i].resize(kNumBlockHorizontal);
		}

		debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);
	   
	}



Vector3 GameScene::Transform(const Vector3& vector, const Matrix4x4& matrix) { return Vector3(); }


void GameScene::Update() 
{ 
	player_->Update(); 
	debugCamera_->Update();

	#ifdef _DEBUG

	if (input_->TriggerKey(DIK_P))
	{
		if (isDugCameraActive_)
		{
			isDugCameraActive_ = false;
		} else {
			isDugCameraActive_ = true;
		}
	}

#endif // DEBUG


	for (const auto& vt : worldTransformBlocks_)
	{
		for (auto t : vt) {
			if (!t) {
				continue;
			}

			// アフィン変換
			t->matWorld_ = 0;

			// 定数バッファに転送する
			t->TransferMatrix();
		}
	}


}



void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	model_->Draw(worldTransform_, ViewProjection_, tetureHandle_);
	player_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
