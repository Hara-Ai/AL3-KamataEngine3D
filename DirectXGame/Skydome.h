#pragma once
#include "Model.h"
#include "WorldTransform.h"


class Skydome 
{
public:

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

	private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;

	Model* model_ = nullptr;
};
