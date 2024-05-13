#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();



private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	WorldTransform worldTransform_;

//	Matrix4x4 = 

	ViewProjection ViewProjection_;

	uint32_t tetureHandle_ = 0;

	Model* model_ = nullptr;

	Player* player_ = nullptr;

	Model* blockModel_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	Model* block_ = nullptr;
	uint32_t blockTextureHandle_ = 0u;

	DebugCamera* debugCamera_ = nullptr;
	uint32_t isDugCameraActive_ = 0u;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
