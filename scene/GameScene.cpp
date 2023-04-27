#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"MathUtilityForText.h"

//コンストラクタ
GameScene::GameScene()
{

}

//デストラクタ
GameScene::~GameScene()
{
	delete playerModel_;
	delete spriteBG_;
	delete stageModel_;
}

//初期化
void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//ここから

	//BG(2Dスプライト)
	bgTexHundle_ = TextureManager::Load("bg.jpg");	
	spriteBG_ = Sprite::Create(bgTexHundle_, {0, 0});
	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	//ステージ
	texHundleStage_ = TextureManager::Load("stage.jpg");
	stageModel_ = Model::Create();
	stageWorldTransform_.Initialize();

	//ステージの位置を変更
	stageWorldTransform_.translation_ = {0, -1.5f, 0};
	stageWorldTransform_.scale_ = {4.5f, 1, 40};
	//変換行列を更新
	stageWorldTransform_.matWorld_ = 
		MakeAffineMatrix
		(stageWorldTransform_.scale_, 
		stageWorldTransform_.rotation_,
	    stageWorldTransform_.translation_);
	//変換行列を定数バッファに転送
	stageWorldTransform_.TransferMatrix();

	//プレイヤー
	texHundlePlayer_ = TextureManager::Load("player.png");
	playerModel_ = Model::Create();
	playerWorldTransform_.scale_ = {0.5f, 0.5f, 0.5};
	playerWorldTransform_.Initialize();

	//ここまで
}

//更新
void GameScene::Update()
{ 
	PlayerUpdate(); 
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

	spriteBG_->Draw();

	//ここまで

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	//ここから

	stageModel_->Draw(stageWorldTransform_, viewProjection_, texHundleStage_);
	playerModel_->Draw(playerWorldTransform_, viewProjection_, texHundlePlayer_);

	//ここまで

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	//ここから



	//ここまで

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::PlayerUpdate()
{
	//変換行列を更新
	playerWorldTransform_.matWorld_ = MakeAffineMatrix(
	    playerWorldTransform_.scale_, 
		playerWorldTransform_.rotation_,
	    playerWorldTransform_.translation_);
	//変換行列をバッファに転送
	playerWorldTransform_.TransferMatrix();
}