#pragma once
#include "Model.h"
#include"WorldTransform.h"

class Player {

public:

	Player();
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
 


private:

	//ワールド変換データ
	WorldTransform worldTransfrom_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	
};
