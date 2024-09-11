#pragma once
#include "AABB.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <MapChipField.h>
#include <AABB.h>

class Player;

class goalObject 
{
public:

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	AABB GetAABB();
	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突応答
	void OnCollision(const Player* player);

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

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* goalModel_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	Input* input_ = nullptr;

	// キャラキターの当たり判定サイズ
	static inline const float kWidth = 1.6f;
	static inline const float kHeigth = 1.6f;

};
