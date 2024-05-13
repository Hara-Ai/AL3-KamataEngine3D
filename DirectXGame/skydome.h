#pragma once
#include <Player.cpp>

class skydome {
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Inialize();

	/// <summary>
	/// XV
	/// </summary>
	
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	
	void Drow();

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};