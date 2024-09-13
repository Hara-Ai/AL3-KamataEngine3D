#pragma once

#include "Audio.h"
#include "CameraController.h"
#include "DeathParticles.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "MoveEnemy.h"
#include "Player.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "goalObject.h"
#include <Bullet.h>
#include <cassert>

// Scene
enum class Phase {
	kPlay,
	kDeath,
};

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	void ChangePhase();

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	// 全ての敵や障害物との当たり判定（マップチップ外）
	void ChecAllCollisiions();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();
	bool IsCollision(AABB aabb1, AABB aabb2);

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }
	bool IsClearF_() const { return clearF_; }
	// bool IsClearR() const { return clearR_; }

	bool IsPlayerAlive() const {
		// プレイヤーオブジェクトが存在し、かつ生存しているかどうかをチェック
		return player_ != nullptr && player_->IsAlive();
	}

private: // メンバ変数
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;
	MapChipField* mapChipField_;
	Skydome* skydome_ = nullptr;
	Player* player_ = nullptr;
	Player* toumeiPlayer_ = nullptr;
	Enemy* enemy_ = nullptr;
	goalObject* goalObject_ = nullptr;

	Model* model_ = nullptr;
	Model* toumeiModel_ = nullptr;
	Model* enmeyModel_ = nullptr;
	Model* moveEnmeyModel_ = nullptr;
	Model* goalModel_ = nullptr;
	Model* bulletEnemyModel_ = nullptr;
	Model* bulletModel_ = nullptr;

	CameraController* CameraController_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	WorldTransform wolrldTransform_ = {};
	ViewProjection viewProjection_ = {};
	MapChipData mapChipData_ = {};
	uint32_t numBlockVirtical_ = 0;
	uint32_t numBlockHorizontal_ = 0;
	uint32_t tetureHandle_ = 0;

	std::list<Enemy*> enemies_;
	std::list<MoveEnemy*> moveEnemies_;
	std::list<EnemyBullet*> bulletEnemies_;
	std::list<Bullet*> bullets_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// デバックカメラ有効
	bool isDebugCameraActiive_ = false;

	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	// デバックカメラのビュープロジェクション
	ViewProjection* debugViewProjection_;

	DeathParticles* deathParticles_;
	// デスパーティクルが存在するか
	bool deathParticlesFlag = false;

	Phase phase_;

	// 終了フラグ
	bool finished_ = false;
	bool clearF_ = false;

	float plus = 0.0f;
	int playerPosX = 1;
	int playerPosY = 18;

	float lifetime = 0.0f;
	float bulletSpeed = 0.0f;

	uint32_t tH = 0;
	Sprite* sprite = nullptr;
};