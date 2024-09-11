#include "MoveEnemy.h"
#include "WorldTransform.h"
#include <numbers>

void MoveEnemy::Initalize(Model* model, ViewProjection* viewProjection, const Vector3& position, Player* player) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	viewProjection_ = viewProjection;
	enemyModel_ = model;
	player_ = player;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void MoveEnemy::Update() {
	if (player_) {

		// フレームごとにプレイヤーの位置を更新
		Vector3 playerPosition = player_->GetWorldTransform().translation_;

		// プレイヤーのY軸回転角度を取得し、向きを計算
		float angleY = player_->GetWorldTransform().rotation_.y;
		Vector3 playerDirection = {cos(angleY), 0.0f, sin(angleY)};

		// 敵の位置や方向ベクトルの更新
		Vector3 enemyPosition = worldTransform_.translation_;
		Vector3 directionToPlayer = {playerPosition.x - enemyPosition.x, playerPosition.y - enemyPosition.y, playerPosition.z - enemyPosition.z};

		// プレイヤーが敵を見ているか判定するため、内積を計算
		float dotProduct = Dot(playerDirection, directionToPlayer);

		// プレイヤーが背を向けているか
		if (dotProduct <= 0.0f) {
			Vector3 directionNormalized = Normalize(directionToPlayer);
			worldTransform_.translation_.x += directionNormalized.x * enemySpeed_;
			worldTransform_.translation_.y += directionNormalized.y * enemySpeed_;
			worldTransform_.translation_.z += directionNormalized.z * enemySpeed_;
		}

		// 行列の更新
		worldTransform_.UpdateMatrix();
	}
}

void MoveEnemy::Draw() { enemyModel_->Draw(worldTransform_, *viewProjection_); }

Vector3 MoveEnemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

AABB MoveEnemy::GetAABB() { return AABB(); }