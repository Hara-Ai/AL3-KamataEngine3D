#pragma once
#include "Model.h"
#include "WorldTransform.h"

// 左右
enum class LRDirection
{
	kRight,
	kLeft,
};

class Player 
{

public:
	Player();
	~Player();

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
	// ワールド変換データ
	WorldTransform worldTransfrom_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	static inline const float kAcceleraion = 0.3f;
	static inline const float kLimitRunSpeed = 0.8f;
	Vector3 velocity_ = {};
};
