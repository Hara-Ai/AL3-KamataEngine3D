#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle,ViewProjection* viewProjection) 
{ 
	assert(model);
	//引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
	//ワールド変換の初期化
	worldTransform_;
}

void Player::Update() 
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}


void Player::Draw() 
{ model_->Draw(worldTransform_, viewProjection_, textureHandle_); }
