#include "TitleScene.h"
#include <dinput.h>

TitleScene::TitleScene() : isFinished_(false) {
	// コンストラクタの内容
}

TitleScene::~TitleScene() {
	// デストラクタの内容
}

void TitleScene::Initialize() // 初期化処理
{
	isFinished_ = false;
}

void TitleScene::Update() // 更新処理
{

	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		isFinished_ = true;
	}
}

void TitleScene::Draw() // 描画処理
{
	
}
