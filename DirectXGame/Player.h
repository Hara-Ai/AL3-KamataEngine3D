#pragma once
#include "GameScene.h"
#include "GameScene.cpp"

class Player {

public:

	Player Initialize();
	Player Update(); 
	Player Draw();
	void Initialize(Model* model, uint32_t textureHandle);


private:

	//ワールド変換データ
	WorldTransform worldTransfrom_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	
	
};
