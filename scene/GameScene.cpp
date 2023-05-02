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
	//プレイヤー
	delete playerModel_;
	//ビーム
	delete beamModel_;
	//敵
	delete enemyModel_;
	//背景
	delete spriteBG_;
	//床
	delete stageModel_;
}

//初期化
void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//ここから

	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	//BG(2Dスプライト)
	bgTexHundle_ = TextureManager::Load("bg.jpg");	
	spriteBG_ = Sprite::Create(bgTexHundle_, {0, 0});

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
	playerWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	playerWorldTransform_.Initialize();

	//ビーム
	texHundleBeam_ = TextureManager::Load("beam.png");
	beamModel_ = Model::Create();
	beamWorldTransform_.scale_ = {0.3f, 0.3f, 0.3f};
	beamWorldTransform_.Initialize();

	//敵
	texHundleEnemy_ = TextureManager::Load("enemy.png");
	enemyModel_ = Model::Create();
	enemyWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWorldTransform_.Initialize();

	//ここまで
}

//更新
void GameScene::Update()
{ 
	PlayerUpdate();
	BeamUpdate();
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

	//床
	stageModel_->Draw(stageWorldTransform_, viewProjection_, texHundleStage_);
	//プレイヤー
	playerModel_->Draw(playerWorldTransform_, viewProjection_, texHundlePlayer_);
	//ビーム
	if (beamFlag_)
	{
		beamModel_->Draw(beamWorldTransform_, viewProjection_, texHundleBeam_);
	}
	enemyModel_->Draw(enemyWorldTransform_, viewProjection_, texHundleEnemy_);

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
	//キーによる移動処理
	if (input_->PushKey(DIK_RIGHT))
	{
		playerWorldTransform_.translation_.x += 0.1f;
	}
	else if (input_->PushKey(DIK_LEFT))
	{
		playerWorldTransform_.translation_.x -= 0.1f;
	}

	if (playerWorldTransform_.translation_.x < -4)
	{
		playerWorldTransform_.translation_.x = -4;
	}
	if (playerWorldTransform_.translation_.x > 4)
	{
		playerWorldTransform_.translation_.x = 4;
	}

	//変換行列を更新
	playerWorldTransform_.matWorld_ = MakeAffineMatrix(
	    playerWorldTransform_.scale_, 
		playerWorldTransform_.rotation_,
	    playerWorldTransform_.translation_);
	//変換行列をバッファに転送
	playerWorldTransform_.TransferMatrix();
}

void GameScene::BeamUpdate()
{
	//初期化
	BeamBorn();
	//移動
	BeamMove();

	// 変換行列を更新
	beamWorldTransform_.matWorld_ = MakeAffineMatrix(
	    beamWorldTransform_.scale_, 
		beamWorldTransform_.rotation_,
	    beamWorldTransform_.translation_);
	// 変換行列をバッファに転送
	beamWorldTransform_.TransferMatrix();
}

void GameScene::BeamBorn()
{
	if (input_->TriggerKey(DIK_SPACE) && !beamFlag_)
	{
		beamFlag_ = true;
		beamWorldTransform_.translation_.x = playerWorldTransform_.translation_.x;
		beamWorldTransform_.translation_.z = playerWorldTransform_.translation_.z;
	}
}

void GameScene::BeamMove()
{
	if (beamFlag_)
	{
		beamWorldTransform_.translation_.z += 0.5f;
		beamWorldTransform_.rotation_.x += 0.1f;
	}

	if (beamWorldTransform_.translation_.z >= 40.0f)
	{
		beamFlag_ = false;
	}
}