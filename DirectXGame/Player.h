#pragma once
#include "AABB.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <MapChipField.h>

// #include <GetWorldPosition.h>

class MapChipField;
class Enemy;
class goalObject;
class GetWorldPosition;
class EnemyBullet;
class Bullet;
class MoveEnemy;
// 左右
enum class LRDirection {
	kRight,
	kLeft,
};

enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};

// マップとの当たり判定情報
struct CollisionMapInfo {
	bool CeilingCollisionFlag = false; // 天井衝突フラグ
	bool LandingFlag = false;          // 着地フラグ
	bool WallContactFlag = false;      // 壁接触フラグ
	Vector3 moveMent;                  // 移動量

	bool oneMoreFlag = false; // 一個上のフラグ
};

class Player {

public:
	Player();

	WorldTransform& GetWorldTrnsform();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	// マップ衝突判定
	void MapCollisionDetection(CollisionMapInfo& info);

	void CollisonMapTop(CollisionMapInfo* info);    // 上
	void CollisonMapBottom(CollisionMapInfo* info); // 下
	void CollisonMaplight(CollisionMapInfo* info);  // 右
	void CollisonMapLeft(CollisionMapInfo* info);   // 左
	void ConllosonPlayerBlock(CollisionMapInfo* info);
	// 一個上を見る処理
	// void CheckUpperMapChipAndInput(CollisionMapInfo* info);

	// 判定結果を反映して移動させる
	void Move(const CollisionMapInfo& info);
	// 天井に接している場合の処理
	void attachedCeiling(const CollisionMapInfo& info);
	// 着地状態の切り替え処理
	void SwitchingState(CollisionMapInfo& info);
	// 壁接触による減速
	void attachedWallCeiling(const CollisionMapInfo& info);

	// 半透明時に上にブロックがあった際の処理
	void CollisononeMoreFlag(const CollisionMapInfo& info);
	// AABBを取得
	AABB GetAABB();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	void OnEnemyCollision(const Enemy* enemy);
	void OnEnemyBulletCollision(const EnemyBullet* enemy);
	void OnBulletCollision(const Bullet* enemy);
	void OnEnemyMoveCollision(const MoveEnemy* moveEnemy);
	void OnGoalCollision(const goalObject* goal);

	bool IsDead() const { return isDeed_; }
	bool IsClaerF_() const { return clearF_; }

	WorldTransform& GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	// 透明かどうかの判定フラグ
	bool isTranslucent = false;

	MapChipType GetUpperMapChipType(const Vector3& position);

	bool IsAlive() const {
		return isAlive_; // プレイヤーの生存状態を保持するメンバ変数
	}
	bool isAlive_ = true;

private:
	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* playerModel_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	Input* input_ = nullptr;

	LRDirection lrDirection_ = LRDirection::kLeft;

	static inline const float kAcceleraion = 0.2f;
	static inline const float kLimitRunSpeed = 0.2f;
	Vector3 velocity_ = {};

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.2f;

	// 接地状態フラグ
	bool onGround_ = true;

	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 0.01f;
	// ジャンプ速度(上方向)
	static inline const float kJumpAcceleration = 1.0f;

	const Vector3& GetVelocity() const { return velocity_; }

	// キャラキターの当たり判定サイズ
	static inline const float kWidth = 1.6f;
	static inline const float kHeigth = 1.6f;

	static inline const float kBlank = 0.1f;

	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 1.0f;
	// 着地時の速度減衰率
	static inline const float kAttenuationWall = 1.0f;

	bool isDeed_ = false;
	bool clearF_ = false;

	// 切り替えTimer
	uint32_t halfTimer = 0;

	static inline const float kGaq = 0.6f;
};
