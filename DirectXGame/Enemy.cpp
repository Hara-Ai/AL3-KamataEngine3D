#include "Enemy.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	model_ = model;

	// ˆø”‚Ì“à—e‚ðƒƒ“ƒo•Ï”‚É‹L˜^
	viewProjection_ = viewProjection;
}

void Enemy::Update() 
{
	worldTransform_.translation_.x - 1.0f;
}


void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
