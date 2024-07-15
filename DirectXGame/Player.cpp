#include "Player.h"
#include "WorldTransform.h"
#include "ViewProjection.h" 
#include <cassert>
#include <numbers>
#include <Input.h>
#include <algorithm>

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	worldTransfrom_.Initialize();
	worldTransfrom_.translation_ = position;
	worldTransfrom_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	model_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void Player::Update() 
{
	// 行列を定数バッファに転送
	worldTransfrom_.TransferMatrix();

	//移動入力
	//左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		//左右加速
		Vector3 acceleration = {};

		if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			//左移動中の右入力
			if (velocity_.x < 0.0f)
			{
				//速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAcceleraion);
			}
			acceleration .x+= kAcceleraion;

			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
			}
		} 
		else if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			acceleration.x -= kAcceleraion;
			
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
			}
		}

		//右移動中の左入力
		if (velocity_.x < 0.0f)
		{
			//速度と逆方向に入力中は急ブレーキ
			velocity_.x *= (1.0f - kAcceleraion);
		}

		//旋回制御
		//左右の自キャラ角度テーブル
		float destinationRotationYTable[] = 
		{
			std::numbers::pi_v<float> / 2.0f, 
			std::numbers::pi_v<float> * 3.0f / 2.0f
		};
		//状態に応じえた角度を取得する
		float destionRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		//自キャラの角度を設定する
		worldTransfrom_.rotation_.y = destionRotationY;

		//加速/減速
		velocity_.x += acceleration.x;

		//最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	}
	else 
	{
		//非入力時は移動減衰をかける
		velocity_.x *= (1.0f - kAcceleraion);
	}

	//移動
	worldTransfrom_.translation_.x += velocity_.x;
	//行列計算
	worldTransfrom_.UpdateMatrix();
}

void Player::Draw()
{ 
	model_->Draw(worldTransfrom_, *viewProjection_, textureHandle_);
}

