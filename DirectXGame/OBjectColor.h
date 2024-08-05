#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <MapChipField.h>
#include "Vector4.h"

class OBjectColor {
public:
	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	// コンストラクタ
	OBjectColor();

	void SetColor(const Vector4& color) { color_ = color; };
	void TransferMatrix();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	void Initialize();

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
	Model* model_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	//// 存続時間
	static inline const float kDuration = 1.0f;
	//// 移動の速さ
	static inline const float kSpeed = 1.0f;
	//// 分割した１個分の角度
	static inline const float kAngleUnit = (2.0f * 3.14f) / 8.0f;

	// 終了Flag
	bool isFinished_ = false;
	// 経過時間カウント
	float counter_ = 0.0f;

	// 色変更オブジェクト
	//OBjectColor objectColor_;
	// 色の数値
	Vector4 color_;
};
