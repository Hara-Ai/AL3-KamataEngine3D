#include "TitleScene.h"
#include "CameraController.h"
#include "Enemy.h"
#include "GameScene.h"
#include "ObjectColor.h"
#include "Player.h"
#include "Skydome.h"
#include "TextureManager.h"
#include <AABB.h>
#include <cassert>
#include <dinput.h>
#include <numbers>

TitleScene::TitleScene() : isFinished_(false) {
	// コンストラクタの内容
}

TitleScene::~TitleScene() { delete player_; }



void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	// 3Dモデルの生成(プレイヤー)
	model_ = Model::CreateFromOBJ("player", true);
	
	// 自キャラの生成
	player_ = new Player();
	viewProjection_ = new ViewProjection();

	// プレイヤーの初期位置
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);

	// 自キャラの初期化
	player_->Initialize(model_, viewProjection_, playerPosition);

	player_->SetMapChipField(mapChipField_);


	textureHandle_ = TextureManager::Load("sample.png");

	worldTransform_.Initialize();
	viewProjection_->Initialize();
}

void TitleScene::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		isFinished_ = true;
	}
}

void TitleScene::Draw() 
{

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

		// 自キャラの描画
		//player_->Draw();

		
	    model_->Draw(worldTransform_, *viewProjection_,textureHandle_);

		// 3Dオブジェクト描画後処理
		Model::PostDraw();

#pragma endregion
}




