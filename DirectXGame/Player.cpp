#include "Player.h"
#include <cassert>

Player::Player() {}

Player::~Player() {}

void Player::Update() 
{ 
	//行列を定数バッファに転送
	worldTransfrom_->TransferMatrix();
}

void Player::Draw() 
{ 
	model_->Draw(worldTransfrom_,
	*viewProjection_, 
	textureHandle_); 
}

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) 
{
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransfrom_->Initialize();

	//引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}
