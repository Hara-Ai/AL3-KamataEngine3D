#include "DeathParticles.h"
#include "WorldTransform.h"
#include <cassert>
#include <numbers>
#include <Matrix4x4Function.h>


DeathParticles::DeathParticles() : model_(nullptr), viewProjection_(nullptr) {}


void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	 assert(model);
	 
	//ワールド変換の初期化
	 for (WorldTransform& worldTransform : worldTransforms_)
	{
		 worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	model_ = model;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	
	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;

	//objectColor_.Initialize();
	//color_ = {1, 1, 1, 1};
}

void DeathParticles::Update() 
{
	// ワールド変換の更新
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}

	for (uint32_t i = 0; i < 8; i++)
	{
		// 基本となる速度ベクトル
		Vector3 velocity = {1.0f, 0.0, 0.0};
		// 回転率の計算する
		float angle = 45 * (float)i;
		//Z軸まわり回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		// 基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		// 移動処理
		worldTransforms_[i].translation_ += velocity;
	}

	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration)
	{
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	if (isFinished_)
	{
		return;
	}

	//color_.w = std::clamp(counter_, 0.0f, 1.0f);
	//// 色変更オブジェクトに色の数値を設定する
	//objectColor_.SetColor(color_);
	//// 色変更オブジェクトをVRAMに転送
	//objectColor_.TransferMatrix();

}

void DeathParticles::Draw() 
{ 
	// モデルの描画
	for (auto& worldTransform : worldTransforms_) 
	{
		model_->Draw(worldTransform, *viewProjection_, textureHandle_);
	}

	if (isFinished_) {
		return;
	}
}
