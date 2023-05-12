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
	//タイトル
	delete titleSprite;
	//
	delete enterSprite;
	//
	delete gameoverSprite;
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

	//タイトル
	texHundleTitle_ = TextureManager::Load("title.png");
	titleSprite = Sprite::Create(texHundleTitle_, {0, 0});

	//エンター
	texHundleEnter_ = TextureManager::Load("enter.png");
	enterSprite = Sprite::Create(texHundleEnter_, {400, 360,});

	//ゲームオーバー
	texHundleGameover_ = TextureManager::Load("gameover.png");
	gameoverSprite = Sprite::Create(texHundleGameover_, {0, 100});

	//乱数
	srand((unsigned int)time(NULL));

	//デバッグテキスト
	debugText_ = DebugText::GetInstance();
	debugText_->Initialize();

	//ここまで
}

//更新
void GameScene::Update()
{
	switch (scene)
	{
	case TITLE_:

		TitleUpdate();

		break;

	case GAMEPLAY_:

		GamePlayUpdate();

		break;

	case GAMEOVER_:

		GameoverUpdate();

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

	// ここから

	switch (scene)
	{
	case TITLE_:



		break;

	case GAMEPLAY_:

		GamePlayDraw2DBack();

		break;

	case GAMEOVER_:

		GamePlayDraw2DBack();

		break;
	}

	// ここまで

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここから

	switch (scene)
	{
	case TITLE_:



		break;

	case GAMEPLAY_:

		GamePlayDraw3D();

		break;

	case GAMEOVER_:

		GamePlayDraw3D();

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

	switch (scene)
	{
	case TITLE_:

		TitleDraw2DNear();

		break;

	case GAMEPLAY_:

		GamePlayDraw2DNear();

		break;

	case GAMEOVER_:

		GameoverDraw2DNear();

		break;
	}
	
	debugText_->DrawAll();

	// ここまで

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

	//変換行列を更新
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

void GameScene::EnemyUpdate()
{
	EnemyBorn();
	EnemyMove();

	// 変換行列を更新
	enemyWorldTransform_.matWorld_ = MakeAffineMatrix(
	    enemyWorldTransform_.scale_, 
		enemyWorldTransform_.rotation_,
	    enemyWorldTransform_.translation_);
	// 変換行列をバッファに転送
	enemyWorldTransform_.TransferMatrix();
}

void GameScene::EnemyBorn()
{
	if (!enemyAlive_)
	{
		//乱数でX座標の指定
		int x = rand() % 80;
		float x2 = (float)x / 10 - 4;
		enemyWorldTransform_.translation_.x = x2;
		enemyAlive_ = true;
		enemyWorldTransform_.translation_.z = 40;
	}
}

void GameScene::EnemyMove()
{
	if (enemyAlive_)
	{
		enemyWorldTransform_.translation_.z -= 0.3f;
		enemyWorldTransform_.rotation_.z += 0.2f;

		if (enemyWorldTransform_.translation_.z < -5)
		{
			enemyAlive_ = false;
		}
	}
}

void GameScene::Collision()
{
	CollisionPtoE();
	CollisionBtoE();
}

void GameScene::CollisionPtoE()
{
	//敵が生きていれば
	if (enemyAlive_)
	{
		//差を求める
		float dx = abs(playerWorldTransform_.translation_.x - enemyWorldTransform_.translation_.x);
		float dz = abs(playerWorldTransform_.translation_.z - enemyWorldTransform_.translation_.z);

		//衝突したら
		if (dx < 1 && dz < 1)
		{
			if (playerLife_ > 0)
			{
				playerLife_ -= 1;
			}			
			enemyAlive_ = false;
		}
	}
}

void GameScene::CollisionBtoE()
{
	// 敵が生きていれば
	if (enemyAlive_ && beamFlag_)
	{
		// 差を求める
		float dx = abs(beamWorldTransform_.translation_.x - enemyWorldTransform_.translation_.x);
		float dz = abs(beamWorldTransform_.translation_.z - enemyWorldTransform_.translation_.z);

		// 衝突したら
		if (dx < 1 && dz < 1)
		{
			gameScore_ += 10;
			enemyAlive_ = false;
			beamFlag_ = false;
		}
	}
}

void GameScene::TitleUpdate()
{
	gameTimer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		GamePlayStart();
		scene = GAMEPLAY_;
	}
}

void GameScene::TitleDraw2DNear()
{
	titleSprite->Draw();

	//エンター表示
	if (gameTimer_ % 40 >= 20)
	{
		enterSprite->Draw();
	}
}

void GameScene::GamePlayStart()
{
	gameScore_ = 0;
	playerLife_ = 3;
	enemyAlive_ = false;
	beamFlag_ = false;
	playerWorldTransform_.translation_.x = 0;
}

void GameScene::GamePlayUpdate()
{
	// プレイヤー
	PlayerUpdate();
	// ビーム
	BeamUpdate();
	// エネミー
	EnemyUpdate();
	// 当たり判定
	Collision();

	if (playerLife_ < 1)
	{
		scene = GAMEOVER_;
	}
}

void GameScene::GamePlayDraw3D()
{
	// 床
	stageModel_->Draw(stageWorldTransform_, viewProjection_, texHundleStage_);
	// プレイヤー
	playerModel_->Draw(playerWorldTransform_, viewProjection_, texHundlePlayer_);

	if (scene == GAMEPLAY_)
	{
		// ビーム
		if (beamFlag_)
		{
			beamModel_->Draw(beamWorldTransform_, viewProjection_, texHundleBeam_);
		}
		// 敵
		if (enemyAlive_)
		{
			enemyModel_->Draw(enemyWorldTransform_, viewProjection_, texHundleEnemy_);
		}
	}
}

void GameScene::GamePlayDraw2DBack()
{
	spriteBG_->Draw();
}

void GameScene::GamePlayDraw2DNear()
{
	//ゲームスコア
	char score[100];
	sprintf_s(score, "SCORE : %d", gameScore_);
	debugText_->Print(score, 200, 10, 2);
	//ライフ
	char life[10];
	sprintf_s(life, "LIFE : %d", playerLife_);
	debugText_->Print(life, 840, 10, 2);
}

void GameScene::GameoverUpdate()
{
	gameTimer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		scene = TITLE_;
	}
}

void GameScene::GameoverDraw2DNear()
{
	gameoverSprite->Draw();

	// エンター表示
	if (gameTimer_ % 40 >= 20)
	{
		enterSprite->Draw();
	}
}