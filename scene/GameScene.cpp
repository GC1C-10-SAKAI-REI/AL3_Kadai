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
	//各シーンの消去
	delete title_;
	delete gamePlay_;
	delete gameOver_;
	delete sEnum_;
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

	//各シーンクラスの生成
	title_ = new Title();
	gamePlay_ = new GamePlay();
	gameOver_ = new GameOver();
	sEnum_ = new SceneEnum();

	//各シーンクラスの初期化
	title_->Initialize();
	gamePlay_->Initialize(viewProjection_);
	gameOver_->Initialize(viewProjection_);

	scene_ = TITLE;

	title_->BGMPlay();
}

//更新
void GameScene::Update()
{
	Scene oldScene = scene_;

	switch (scene_)
	{
	case GameScene::TITLE:

		title_->Update(scene_);
		break;

	case GameScene::GAMEPLAY:

		//ゲームプレイ
		gamePlay_->Update(scene_);
		gamePlay_->Shot();
		break;

	case GameScene::GAMEOVER:

		gameOver_->Update(scene_);
		break;

	case GameScene::GAMECLEAR:
		break;

	default:
		break;
	}

	//シーン変更ならば
	if (oldScene != scene_)
	{
		switch (scene_)
		{
		case SceneEnum::TITLE:
			title_->BGMPlay();

			break;

		case SceneEnum::GAMEPLAY:
			gamePlay_->BGMPlay();
			gamePlay_->Start();

			break;

		case SceneEnum::GAMEOVER:
			gamePlay_->Start();

			break;
		}
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

		gamePlay_->Draw2Far();

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

		gamePlay_->Draw3D();

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

		title_->Draw2DNear();
		break;

	case GameScene::GAMEPLAY:

		gamePlay_->Draw2DNear();
		break;

	case GameScene::GAMEOVER:

		gameOver_->Draw2DNear();

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