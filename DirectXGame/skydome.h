#pragma once
#include <Player.cpp>

class skydome {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Inialize();

	/// <summary>
	/// �X�V
	/// </summary>
	
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	
	void Drow();

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};