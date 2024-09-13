#include "GameScene.h"
#include "AABB.h"
#include "AxisIndicator.h"
#include "CameraController.h"
#include "Enemy.h"
#include "ObjectColor.h"
#include "Player.h"
#include "Skydome.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	for (std::vector<WorldTransform*>& worldTansformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTansformBlock : worldTansformBlockLine) {
			delete worldTansformBlock;
		}
	}

	for (Enemy* kenemise_ : enemies_) {
		delete kenemise_;
	}
	for (MoveEnemy* kMoveEnemise_ : moveEnemies_) {
		delete kMoveEnemise_;
	}
	for (EnemyBullet* kBulletEnemise_ : bulletEnemies_) {
		delete kBulletEnemise_;
	}
	for (Bullet* kBullets_ : bullets_) {
		delete kBullets_;
	}

	delete modelBlock_;
	delete modelSkydome_;
	delete skydome_;
	delete player_;
	delete toumeiPlayer_;
	delete enemy_;
	delete goalObject_;
	delete model_;
	delete toumeiModel_;
	delete enmeyModel_;
	delete moveEnmeyModel_;
	delete goalModel_;
	delete bulletEnemyModel_;
	//delete bulletModel_;
	delete deathParticles_;
	delete mapChipField_;
	delete debugCamera_;
}

void GameScene::ChecAllCollisiions() {
	// 衝突対象1と2の座標
	AABB aabb1, aabb2, aabb3;
	AABB aabb4;
	// 自キャラの座標
	aabb1 = player_->GetAABB();
	// 自キャラと敵全ての当たり判定
	for (Enemy* enemy : enemies_) {
		// 敵弾の座標
		aabb2 = enemy->GetAABB();

		// AABB同士の交差判定
		if (IsCollision(aabb1, aabb2)) {

			//// 自キャラの衝突時コールバックを呼び出す
			// player_->OnCollision(enemy);
			//// 敵弾の衝突時コールバックを呼び出す
			// enemy_->OnCollision(player_);
		}
	}
	// 自キャラと敵全ての当たり判定
	for (MoveEnemy* moveEnemy : moveEnemies_) {
		// 敵弾の座標
		aabb4 = moveEnemy->GetAABB();

		// AABB同士の交差判定
		if (IsCollision(aabb1, aabb4)) {

			//// 自キャラの衝突時コールバックを呼び出す
			player_->OnEnemyMoveCollision(moveEnemy);
			//// 敵弾の衝突時コールバックを呼び出す
			moveEnemy->OnCollisiton(player_);
		}
	}
	// ゴールの座標
	aabb3 = goalObject_->GetAABB();

	// AABB同士の交差判定
	if (IsCollision(aabb1, aabb3)) {
		player_->OnGoalCollision(goalObject_);
		goalObject_->OnCollision(player_);
	}
}

void GameScene::Initialize() {

	phase_ = Phase::kPlay;
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	tetureHandle_ = TextureManager::Load("sample.png");
	//----------------------------呼び出しの初期化----------------------------------------
	// 自キャラの生成
	player_ = new Player();
	toumeiPlayer_ = new Player();
	// 敵キャラの生成
	enemy_ = new Enemy();
	// マップチップを使うので呼び出す
	modelBlock_ = Model::Create();
	mapChipField_ = new MapChipField;

	deathParticles_ = new DeathParticles;
	debugCamera_ = new DebugCamera(1280, 720);
	// スカイドームの初期化
	skydome_ = new Skydome();
	// 生成
	CameraController_ = new CameraController;
	// ゴールの生成
	goalObject_ = new goalObject;

	//-----------------------------モデルの呼び込み---------------------------------------
	// 3Dモデルの生成(プレイヤー)
	model_ = Model::CreateFromOBJ("player", true);             // 透明じゃない場合
	toumeiModel_ = Model::CreateFromOBJ("toumeiPlayer", true); // 透明の場合
	// 3Dモデルの生成(敵)
	enmeyModel_ = Model::CreateFromOBJ("enemy", true);
	// moveEnmeyModel_ = Model::CreateFromOBJ("moveEnemy", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	// ゴールの生成
	goalModel_ = Model::CreateFromOBJ("enemy", true);

	bulletEnemyModel_ = Model::CreateFromOBJ("BulletEnemy", true);
	//-------------------------------初期化のために必要な変数-------------------------------

	// プレイヤーの初期位置
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(6, 18);
	// 敵の初期位置
	Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(0, 18);
	// ゴールの初期位置
	Vector3 goalPosition = mapChipField_->GetMapChipPositionByIndex(6, 19);

	const uint32_t kNumBlockVirtical = 20;
	const uint32_t kNumBlockHorizontal = 100;

	// カメラの出力範囲の初期化
	Rect setter = {
	    35.5f + plus,  // 左端
	    160.5f + plus, // 右端
	    19.5f + plus,  // 下端
	    19.0f + plus   // 上端
	};
	//------------------------------初期化-------------------------------------------------

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	skydome_->Initialize(modelSkydome_, &viewProjection_);
	// 自キャラの初期化
	player_->Initialize(model_, &viewProjection_, playerPosition);
	toumeiPlayer_->Initialize(toumeiModel_, &viewProjection_, playerPosition);

	player_->SetMapChipField(mapChipField_);
	toumeiPlayer_->SetMapChipField(mapChipField_);

	// 敵キャラの初期化
	enemy_->Initialize(enmeyModel_, &viewProjection_, enemyPosition);
	enemy_->SetMapChipField(mapChipField_);

	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	GenerateBlocks();

	deathParticles_->Initialize(model_, &viewProjection_, playerPosition);

	// ゴールの初期化
	goalObject_->Initialize(goalModel_, &viewProjection_, goalPosition);
	// goalObject_->SetMapChipField(mapChipField_);

	// カメラコントローラの初期化
	CameraController_->Initialize();       // 初期化
	CameraController_->SetTarget(player_); // 追跡対象をリセット
	CameraController_->Reset();            // リセット(瞬間合わせ)
	CameraController_->SetMovableArea(setter);
	//-----------------------------------------複数の敵の初期化-------------------------------------
	for (int32_t i = 1; i < 19; ++i) {
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition_ = {enemyPosition.x * i, enemyPosition.y * i, enemyPosition.z};
		newEnemy->Initialize(enmeyModel_, &viewProjection_, enemyPosition_);

		enemies_.push_back(newEnemy);
	}
	for (int32_t i = 0; i < 3; ++i) {
		MoveEnemy* newMoveEnemy = new MoveEnemy();
		Vector3 moveEnemyPosition_ = {100 + 30.0f * i, 35, 0};
		newMoveEnemy->Initalize(enmeyModel_, &viewProjection_, moveEnemyPosition_, player_);
		moveEnemies_.push_back(newMoveEnemy);
	}

	// 張り付いてくる敵
	for (uint32_t i = 0; i < 3; ++i) {
		if (i % 2 == 0) {
			bulletSpeed = 0.015f;
		} else {
			bulletSpeed = 0.020f;
		}

		EnemyBullet* newEnemy = new EnemyBullet();
		Vector3 enemyBulletPosition = {100.f + 30.f * i, 36.f, 0};
		newEnemy->Initalize(bulletEnemyModel_, &viewProjection_, enemyBulletPosition);
		bulletEnemies_.push_back(newEnemy);

		for (uint32_t j = 0; j < 3; ++j) { // 各敵に対して3つの弾を生成
			Bullet* newBullet = new Bullet();
			Vector3 bulletPosition = {100.f + 30.f * i, 36.f, 0}; // 弾の位置を調整
			Vector3 direction;
			if (j == 0) {
				// 1つ目の弾は真っ直ぐ下に飛ばす
				direction = {0.0f, -1.0f, 0.0f};
			} else if (j == 1) {
				// 2つ目の弾を左斜め下に飛ばす
				direction = {-0.7f, -1.0f, 0.0f};
			} else if (j == 2) {
				// 3つ目の弾を右斜め下に飛ばす
				direction = {0.7f, -1.0f, 0.0f};
			}

			newBullet->Initalize(bulletEnemyModel_, &viewProjection_, bulletPosition, lifetime, bulletSpeed, direction);
			bullets_.push_back(newBullet);
		}
	}

#ifdef _DEBUG
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
#endif
}

void GameScene::Update() {

	switch (phase_) {
	case Phase::kPlay:

		if (player_->IsDead()) {
			phase_ = Phase::kDeath;
			const Vector3& deathParticlesPosition = player_->GetWorldPosition();
			deathParticles_->Initialize(model_, &viewProjection_, deathParticlesPosition);
		}

		skydome_->Update();
		// 自キャラの更新
		player_->Update();
		toumeiPlayer_->Update();
		// 敵キャラの更新
		enemy_->Update();
		for (Enemy* kenemise_ : enemies_) {
			kenemise_->Update();
		}

		for (MoveEnemy* kMoveEnemise_ : moveEnemies_) {
			kMoveEnemise_->Update();
		}
		// for (EnemyBullet* kBulletEnemise_ : bulletEnemies_) {
		//	kBulletEnemise_->Update();
		// }
		//  上に張り付いている敵
		for (EnemyBullet* enemy : bulletEnemies_) {
			if (!enemy) {
				continue;
			} else {
				for (Bullet* bullet : bullets_) {
					if (!bullet) {
						continue;
					}

					bullet->Update();
				}
				enemy->Update();
				// CheckAllCollisios();
			}
		}
		// ゴールの更新
		goalObject_->Update();
		// 全ての当たり判定を行う
		ChecAllCollisiions();

		for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock) {
					continue;
				} else {
					worldTransformBlock->UpdateMatrix();
				}
			}
		}

		if (input_->TriggerKey(DIK_A)) {
			plus--;
			CameraController_->Update();
		}

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_P)) {
			isDebugCameraActiive_ = true;
		}
#endif
		debugCamera_->Update();

		if (isDebugCameraActiive_) {
			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			viewProjection_.TransferMatrix();
		} else {
			CameraController_->Update();
			viewProjection_.matView = CameraController_->GetViewProjection().matView;
			viewProjection_.matProjection = CameraController_->GetViewProjection().matProjection;
			// ビュープロジェクション行列の転送
			viewProjection_.TransferMatrix();
		}

		break;
	case Phase::kDeath:

		// 敵キャラの更新
		enemy_->Update();
		for (Enemy* kenemise_ : enemies_) {
			kenemise_->Update();
		}
		if (player_->IsDead()) {
			deathParticles_->Update();
		}

		if (deathParticles_ && deathParticles_->IsFinished()) {
			finished_ = true;
		}

		break;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	switch (phase_) {
	case Phase::kPlay:

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

		// 透明な場合
		if (player_->isTranslucent == true) {
			// 自キャラの描画
			toumeiPlayer_->Draw();
		}

		// 未透明な場合
		if (player_->isTranslucent == false) {
			// 自キャラの描画
			player_->Draw();
		}

		// 敵キャラの描画
		enemy_->Draw();
		for (Enemy* kenemise_ : enemies_) {
			kenemise_->Draw();
		}
		for (MoveEnemy* kMoveEnemise_ : moveEnemies_) {
			kMoveEnemise_->Draw();
		}

		for (EnemyBullet* enemy : bulletEnemies_) {
			if (!enemy) {
				continue;
			} else {
				enemy->Draw();
			}
			for (Bullet* bullet : bullets_) {
				if (bullet) { // nullptr ではない弾を描画
					bullet->Draw();
				}
			}
		}
		// ゴールの描画
		goalObject_->Draw();

		// 天球の描画
		skydome_->Draw();
		// マップチップの描画
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

		break;
	case Phase::kDeath:

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

		// 敵キャラの描画
		enemy_->Draw();
		for (Enemy* kenemise_ : enemies_) {
			kenemise_->Draw();
		}
		// 天球の描画
		skydome_->Draw();

		// マップチップの描画
		for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				modelBlock_->Draw(*worldTransformBlock, viewProjection_);
			}
		}

		if (player_->IsDead()) {
			// パーティクルの描画
			deathParticles_->Draw();
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

		break;
	}
}

void GameScene::GenerateBlocks() {
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVirtical);

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t x = 0; numBlockVirtical > x; x++) {
		for (uint32_t y = 0; numBlockHorizontal > y; y++) {

			if (mapChipField_->GetMapChipTypeByIndex(y, x) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();

				worldTransformBlocks_[x][y] = worldTransform;
				worldTransformBlocks_[x][y]->translation_ = mapChipField_->GetMapChipPositionByIndex(y, x);
			}
		}
	}
}

bool GameScene::IsCollision(AABB aabb1, AABB aabb2) {
	bool ATFlag = false;

	// 当たってるか当たってないか判断するフラグ
	if (aabb1.max.y > aabb2.min.y && aabb1.min.y < aabb2.max.y) {

		if (aabb1.max.x > aabb2.min.x && aabb1.min.x < aabb2.max.x) {
			ATFlag = true;
		}
	} else {
		ATFlag = false;
	}

	return ATFlag;
}
