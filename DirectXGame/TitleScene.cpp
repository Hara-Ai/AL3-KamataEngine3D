#include "TitleScene.h"
#include <dinput.h>

TitleScene::TitleScene() : isFinished_(false) {
	// コンストラクタの内容
}

TitleScene::~TitleScene() {
	// デストラクタの内容
}

void TitleScene::Initialize() {
	// 初期化処理
}

void TitleScene::Update(char* keys, char* preKeys) {
	// 更新処理
	if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
		isFinished_ = true;
	}
}

void TitleScene::Draw() {
	// 描画処理
}
