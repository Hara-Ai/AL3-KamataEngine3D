#include "DeathParticles.h"
#include <cassert>
#include <numbers>


void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) 
{
	assert(model);
	//ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_)
	{
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	model_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void DeathParticles::Update() 
{
	// ワールド変換の更新
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}
}

void DeathParticles::Draw() 
{ 
	// モデルの描画
	for (auto& worldTransform : worldTransforms_) 
	{
		model_->Draw(worldTransform, *viewProjection_, textureHandle_);
	}
}
