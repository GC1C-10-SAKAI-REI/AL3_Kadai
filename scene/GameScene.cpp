#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

//コンストラクタ
GameScene::GameScene()
{

}

//デストラクタ
GameScene::~GameScene()
{
	delete gamePlay_;
}

//初期化
void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	//ゲームプレイクラス
	gamePlay_ = new GamePlay();
	gamePlay_->Initialize();
}

//更新
void GameScene::Update()
{
	gamePlay_->Update();
}

//描画
void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	//ここから

	gamePlay_->Draw2Far();

	//ここまで

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここから

	gamePlay_->Draw3D();

	// ここまで

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// ここから

	gamePlay_->Draw2DNear();

	// ここまで

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}