#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome 
{
public:

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
};
