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
	// 速度を設定する
	velocity_ = 
	{
	    -kWalkSpeed,
	    0,
	    0,
	};

	walkTikmer_ = 0;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	model_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void Enemy::Update() {
	// 敵の移動処理
	worldTransform_.translation_ += velocity_;
	// タイマーを加算
	walkTikmer_ += 1.0f / 60.0f;

	// 回転アニメーション
	float param = std::sin(velocity_.z);
	float radian = 
		kWalkMotionAngleStart + kWalkMotionAngleEnd
		* (param + 1.0f) / 2.0f;

	//度をラジアンに変換
	float param = (radian);

	worldTransform_.UpdateMatrix();

}


void Enemy::Draw() 
{
	model_->Draw(worldTransform_, *viewProjection_); 
}

