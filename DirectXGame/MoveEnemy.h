#pragma once

#include "Model.h"
#include "Player.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cmath>
#include "AABB.h"
class MapChipField;
class Player;

class MoveEnemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initalize(Model* model, ViewProjection* viewProjection, const Vector3& position, Player* player);

	/// <summary>
	/// 処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 外部からポインタを呼ぶ
	/// </summary>
	void SetMapChipField(MapChipField* mapChipField);

	/// <summary>
	/// 自キャラのワールド座標
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// AABB取得関数
	/// </summary>
	/// <returns></returns>
	AABB GetAABB();
	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="player"></param>
	void OnCollisiton(const Player* player);

	/// <summary>
	/// 内積の関数
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	float Dot(const Vector3& v1, const Vector3& v2) {
		float a = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		return a;
	}
	float Length(const Vector3& v) { return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
	/// <summary>
	/// 正規化の関数
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	Vector3 Normalize(const Vector3& vec) {
		float length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		if (length == 0.0f) {
			return {0.0f, 0.0f, 0.0f}; 
		}
		return {vec.x / length, vec.y / length, vec.z / length};
	}

private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_;
	Model* enemyModel_ = nullptr;
	Player* player_;
	MapChipField* mapChipField_ = nullptr;
	// 敵の歩き速度
	static inline const float kMoveSpeed = 0.001f;
	// 移動量
	Vector3 velocity_ = {};

	// 経過時間
	float walkTimer_ = 0.0f;
	// π
	const double PI = 3.141593;

	// キャラクターの当たり判定のサイズ
	static inline const float kWidth = 1.6f;
	static inline const float kHeight = 1.6f;
	float enemySpeed_ = 0.02f;
	
	float isA = true;
};