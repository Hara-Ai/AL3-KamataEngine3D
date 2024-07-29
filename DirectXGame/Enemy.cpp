//#include "Enemy.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include <Input.h>
//#include <algorithm>
//#include <cassert>
//#include <numbers>
//
//Enemy::Enemy() {}
//
//Enemy::~Enemy() {}
//
//void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
//	assert(model);
//	worldTransform_.Initialize();
//	worldTransform_.translation_ = position;
//
//	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
//	model_ = model;
//
//	// 引数の内容をメンバ変数に記録
//	viewProjection_ = viewProjection;
//}
//
//void Enemy::Update() 
//{
//	worldTransform_.translation_.x - 1.0f;
//}
//
//
//void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); }
