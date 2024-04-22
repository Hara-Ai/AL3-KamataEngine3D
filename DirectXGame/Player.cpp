#include "Player.h"
#include <cassert>

void Player::Initialize() {}

void Player::Update() 
{ 
	//行列を定数バッファに転送
	//worldTransfrom_.TransferMatrix();
}

void Player::Draw() {}

void Player::Initialize(Model* model, uint32_t textureHandle) 
{
	assert(model);
	textureHandle;
}
