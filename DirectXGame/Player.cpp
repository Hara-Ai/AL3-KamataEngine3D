#define NOMINMAX
#include "Player.h"
#include "MapChipField.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>
#include "Player.h"


Player::Player() {}

Player::~Player() {}

WorldTransform& Player::GetWorldTrnsform() { return worldTransfrom_; }

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
	    {+kWidth / 2.0f, -kHeigth / 2.0f, 0}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeigth / 2.0f, 0}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeigth / 2.0f, 0}, //  kRightTop
	    {-kWidth / 2.0f, +kHeigth / 2.0f, 0}, //  kLeftTop
	};
	return center + offsetTable[static_cast<uint32_t>(corner)];
}

void Player::MapCollisionDetection(CollisionMapInfo& info) { CollisonMapTop(info); }

// 上方向衝突判定
void Player::CollisonMapTop(CollisionMapInfo& info) {
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransfrom_.translation_ + info.moveMent, static_cast<Corner>(i));
	}

	// 上昇あり?
	if (info.moveMent.y <= 0) {
		return;
	}

	MapChipType mapChpiType;
	// 真上の当たり判定を行う
	bool hit = false;

	// 左上点の判定
	IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPoition(positionsNew[kLeftTop]);
	mapChpiType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChpiType == MapChipType::kBlock) {
		hit = true;
	}
	// 右上の判定
	indexSet = mapChipField_->GetMapChipIndexSetByPoition(positionsNew[kRightTop]);
	mapChpiType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChpiType == MapChipType::kBlock) {
		hit = true;
	}

	// ブロックにヒット?
	if (hit) 
	{
		//めり込みを排除する方向に移動量を設定する
		indexSet = mapChipField_->GetMapChipIndexSetByPoition();
		// めり込み先ブロックの範囲短形
		

	}
}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	worldTransfrom_.Initialize();
	worldTransfrom_.translation_ = position;
	worldTransfrom_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	model_ = model;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void Player::Update() {

	bool landing = false;

	// ①移動入力
	// //接地状態
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}

		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};

			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAcceleraion);
				}
				acceleration.x += kAcceleraion;

				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始の角度を記録する
					turnFirstRotationY_ = static_cast<float>(lrDirection_);
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				acceleration.x -= kAcceleraion;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始の角度を記録する
					turnFirstRotationY_ = static_cast<float>(lrDirection_);
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
			}

			// 右移動中の左入力
			if (velocity_.x < 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAcceleraion);
			}

			// 旋回制御
			if (turnTimer_ > 0.0f) {
				turnTimer_ = turnTimer_ - 1.0f / 60.0f;

				// 左右の自キャラ角度テーブル
				float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
				// 状態に応じえた角度を取得する
				float destionRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
				// 自キャラの角度を設定する
				worldTransfrom_.rotation_.y = std::lerp(turnFirstRotationY_, destionRotationY, 1 - (turnTimer_ / kTimeTurn));
			}

			// 加速/減速
			velocity_.x += acceleration.x;

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAcceleraion);
		}
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			// ジャンプ初速
			velocity_ += Vector3(0, kJumpAcceleration, 0);
		}
	}
	// 空中
	else {
		// 落下速度
		velocity_ = Vector3(0, -kGravityAcceleration, 0);
		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	// 地面との当たり判定
	// 降下中?
	if (velocity_.y < 0) {
		// Y座標が地面いかになったら着地
		if (worldTransfrom_.translation_.y <= 1.0f) {
			landing = true;
		}
		if (landing) {
			// めり込み排斥
			worldTransfrom_.translation_.y = 1.0f;
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAcceleraion);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}

	// ②移動情報初期化
	CollisionMapInfo collisionMapInfo;

	// 移動量に速度の値をコピー
	collisionMapInfo.moveMent = velocity_;

	// マップ衝突チェック
	MapCollisionDetection(collisionMapInfo);

	// 移動
	worldTransfrom_.translation_ += velocity_;

	// 行列を定数バッファに転送
	worldTransfrom_.TransferMatrix();
	// 行列計算
	worldTransfrom_.UpdateMatrix();
}

void Player::Draw() { model_->Draw(worldTransfrom_, *viewProjection_, textureHandle_); }
