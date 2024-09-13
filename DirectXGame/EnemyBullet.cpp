#include "EnemyBullet.h"
#include "Vector3.h"
#include <numbers>

void EnemyBullet::Initalize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 1.5f;

	viewProjection_ = viewProjection;
	enemyModel_ = model;

	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;
}

void EnemyBullet::Update() {
	// アニメーションのタイマーを加算
	// walkTimer_ += 1.0f / 30.0f;
	////float param = std::sin(walkTimer_-kWalkMotionTime);
	// float param = std::sin(walkTimer_/kWalkMotionTime);
	// float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	// worldTransform_.rotation_.x = radian * ((float)PI/ 180);
	// worldTransform_.translation_ += velocity_;
	// bullet_.Update();
	//  行列計算
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void EnemyBullet::Draw() { enemyModel_->Draw(worldTransform_, *viewProjection_); }

void EnemyBullet::SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

AABB EnemyBullet::GetAABB() {
	Vector3 worldPos = GetWorldPosition();

	AABB aabb;
	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};
	return aabb;
}

void EnemyBullet::OnCollisiton(const Player* player) { (void)player; }