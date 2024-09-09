#pragma once
#include "Input.h"
#include "Player.h"
#include "Model.h"
#include "MapChipField.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"

class TitleScene 
{
public:
	TitleScene();
	~TitleScene();
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

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return isFinished_; }

	private:

	bool isFinished_;

private:

	Input* input_ = nullptr; 
	Player* player_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	// マップチップによるフィールド
	MapChipField* mapChipField_;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// ビュープロジェクション
	ViewProjection* viewProjection_ = {};
};
