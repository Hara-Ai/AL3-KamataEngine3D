#pragma once
#include "Model.h"
#include "WorldTransform.h"

class MapChipField;

// 左右
enum class LRDirection
{
	kRight,
	kLeft,
};

enum Corner
{
	kRightBottom, //右下
	kLeftBottom,  //左下
	kRightTop,    //右上
	kLeftTop,     //左上

	kNumCorner    //要素数
};

//マップとの当たり判定情報
struct CollisionMapInfo 
{
	bool CeilingCollisionFlag = false; //天井衝突フラグ
	bool LandingFlag = false;          //着地フラグ
	bool WallContactFlag = false;      //壁接触フラグ
	Vector3 moveMent;                  // 移動量
};

class Player 
{

public:
	Player();
	~Player();

	WorldTransform& GetWorldTrnsform();

	void SetMapChipField(MapChipField* mapChipField) 
	{ 
		mapChipField_ =  mapChipField;
	}

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	//マップ衝突判定
	void MapCollisionDetection(CollisionMapInfo& info);

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

private:
	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransfrom_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	LRDirection lrDirection_ = LRDirection::kLeft;

	static inline const float kAcceleraion = 0.3f;
	static inline const float kLimitRunSpeed = 0.8f;
	Vector3 velocity_ = {};

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	// 接地状態フラグ
	bool onGround_ = true;

	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.2f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 2.0f;
	// ジャンプ速度(上方向)
	static inline const float kJumpAcceleration = 2.0f;

	const Vector3& GetVelocity() const 
	{
		return velocity_; 
	}

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeigth = 0.8f;

};
