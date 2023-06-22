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
	switch (scene_)
	{
	case GameScene::TITLE:
		break;

	case GameScene::GAMEPLAY:

		//ゲームプレイ
		gamePlay_->Update();

		break;

	case GameScene::GAMEOVER:
		break;

	case GameScene::GAMECLEAR:
		break;

	default:
		break;
	}
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

	switch (scene_)
	{
	case GameScene::TITLE:
		break;

	case GameScene::GAMEPLAY:

		gamePlay_->Draw2Far();

		break;

	case GameScene::GAMEOVER:
		break;

	case GameScene::GAMECLEAR:
		break;

	default:
		break;
	}

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

	switch (scene_)
	{
	case GameScene::TITLE:
		break;

	case GameScene::GAMEPLAY:

		gamePlay_->Draw3D();

		break;

	case GameScene::GAMEOVER:
		break;

	case GameScene::GAMECLEAR:
		break;

	default:
		break;
	}

	// ここまで

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// ここから

	switch (scene_)
	{
	case GameScene::TITLE:
		break;

	case GameScene::GAMEPLAY:

		gamePlay_->Draw2DNear();

		break;

	case GameScene::GAMEOVER:



		break;

	case GameScene::GAMECLEAR:
		break;

	default:
		break;
	}

	// ここまで

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}