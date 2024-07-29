#pragma once
#include "Model.h"
#include "WorldTransform.h"

class MapChipField;

/// <summary>
/// 敵
/// </summary>
class Enemy 
{
public:
	
	Enemy();
	~Enemy();


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
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};
