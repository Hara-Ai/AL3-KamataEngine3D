#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle,ViewProjection* viewProjection) 
{ 
	assert(model);
	//�����̓��e�������o�ϐ��ɋL�^
	viewProjection_ = viewProjection;
	//���[���h�ϊ��̏�����
	worldTransform_;
}

void Player::Update() 
{
	// �s���萔�o�b�t�@�ɓ]��
	worldTransform_.TransferMatrix();
}


void Player::Draw() 
{ model_->Draw(worldTransform_, viewProjection_, textureHandle_); }
