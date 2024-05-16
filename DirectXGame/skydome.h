#pragma once
#include <Player.cpp>

class skydome {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Inialize();

	/// <summary>
	/// 更新
	/// </summary>
	
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	
	void Drow();

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};