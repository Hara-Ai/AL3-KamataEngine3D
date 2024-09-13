#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete clearModel_;
	delete model;
}

void TitleScene::Initalize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model = Model::CreateFromOBJ("GameTitleScene", true);

	clearModel_ = new TitleModel();
	Vector3 clearPosition = {0.f, 0.f, 0.0f};
	viewProjection_.Initialize();
	clearModel_->Initalize(model, &viewProjection_, clearPosition);
}

void TitleScene::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	clearModel_->Update();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	clearModel_->Draw();
	// sprite_->Draw();
	//  3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
