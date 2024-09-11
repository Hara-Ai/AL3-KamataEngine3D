#include "goalObject.h"
#include <numbers>
#include <cassert>

AABB goalObject::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeigth / 2.0f, worldPos.z - kWidth / 2.0f};

	aabb.max = {
	    worldPos.x + kWidth / 2.0f,
	    worldPos.y + kHeigth / 2.0f,
	    worldPos.z + kWidth / 2.0f,
	};

	return aabb;
}

Vector3 goalObject::GetWorldPosition() { // ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動分を取得（ワールド座標）
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}

void goalObject::OnCollision(const Player* player) 
{ (void)player; }

void goalObject::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.x = 120.f;
	worldTransform_.translation_.y = 10.f;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	goalModel_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
	input_ = Input::GetInstance();
}

void goalObject::Update() 
{	
	worldTransform_.UpdateMatrix();
}

void goalObject::Draw() 
{ 
	goalModel_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
}
