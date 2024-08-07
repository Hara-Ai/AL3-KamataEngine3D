#pragma once
#include "Input.h"
#include "Player.h"

class TitleScene 
{
public:
	TitleScene();
	~TitleScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return isFinished_; }

	private:

	bool isFinished_;

	private:
	Input* input_ = nullptr; 

};
