#include "GameScene.h"
#include "TextureManager.h"
#include "Skydome.h"
#include "Matrix4x4Function.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	for (std::vector<WorldTransform*>& worldTansformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTansformBlock : worldTansformBlockLine)
		{
			delete worldTansformBlock;
		}
	}
	worldTransformBlocks_.clear();
	delete modelBlock_;
	delete modelSkydome_;
	delete mapChipField_;
	delete skydome_;
	delete modelSkydome_;
	delete debugCamera_;
	delete player_;
}

void GameScene::Initialize() {

	const float height = 720;
	const float width = 1080;

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	const uint32_t kNumBlockVirtical = 20;
	const uint32_t kNumBlockHorizontal = 100;

	numBlockVirtical_ = 20;
	numBlockHorizontal_ = 100;

	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	worldTransformBlocks_.resize(kNumBlockVirtical);

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * i;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * j;
		}
	}
	


	modelBlock_ = Model::Create();
	modelSkydome_ = Model::Create();
	mapChipField_ = new MapChipField;
	skydome_ = new Skydome();
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");


	skydome_->Initialize();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	wolrldTransform_.Initialize();
	viewProjection_.Initialize();
	wolrldTransform_;
	mapChipData_ = {};

	debugCamera_ = new DebugCamera(width, height);

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize();


	GenerateBlocks();

}

void GameScene::Update() 
{
	skydome_->Update();
	//自キャラの更新
	player_->Update();

	for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
		}
	}

	for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_)
	{
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			worldTransformBlock->UpdateMatrix();
		}
	}

	debugCamera_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_P))
	{
		isDebugCameraActiive_ = true;
	}
	#endif

	if (isDebugCameraActiive_)
	{

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

	//自キャラの描画
	player_->Draw();
	//天球の描画
	skydome_->Draw(wolrldTransform_, viewProjection_);

	for (uint32_t i = 0; i < numBlockVirtical_; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal_; ++j) {
		
			if (mapChipField_->GetMapChipTypeByIndex(i, j) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(i, j);
			}
		}
	}

	//マップチップの描画
	for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

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

void GameScene::GenerateBlocks() 
{
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	

	worldTransformBlocks_.resize(numBlockVirtical);

	for (uint32_t i = 0; i < numBlockVirtical; ++i)
	{
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t x = 0; numBlockVirtical > x;x++)
	{
		for (uint32_t y = 0; numBlockHorizontal > y;y++)
		{
			if (mapChipField_->GetMapChipTypeByIndex(y, x) == MapChipType::kBlock) 
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				
				worldTransformBlocks_[x][y] = worldTransform;
				worldTransformBlocks_[x][y]->translation_ = mapChipField_->GetMapChipPositionByIndex(y, x);
			}
		}
	}

}

