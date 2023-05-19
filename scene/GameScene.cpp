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
	texHundleStage_ = TextureManager::Load("stage2.jpg");
	stageModel_ = Model::Create();
	for (int i = 0; i < stageVal; i++)
	{
		stageWorldTransform_[i].Initialize();
	}

	for (int i = 0; i < stageVal; i++)
	{
		// ステージの位置を変更
		stageWorldTransform_[i].translation_ = {0, -1.5f, 2.0f * i - 5};
		stageWorldTransform_[i].scale_ = {4.5f, 1, 1};
		// 変換行列を更新
		stageWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    stageWorldTransform_[i].scale_, stageWorldTransform_[i].rotation_,
		    stageWorldTransform_[i].translation_);
		// 変換行列を定数バッファに転送
		stageWorldTransform_[i].TransferMatrix();
	}

	//プレイヤー
	texHundlePlayer_ = TextureManager::Load("player.png");
	playerModel_ = Model::Create();
	playerWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	playerWorldTransform_.Initialize();

	//ビーム
	texHundleBeam_ = TextureManager::Load("beam.png");
	beamModel_ = Model::Create();
	for (int i = 0; i < remainBeam; i++)
	{
		beamWorldTransform_[i].scale_ = {0.3f, 0.3f, 0.3f};
		beamWorldTransform_[i].Initialize();
	}

	//敵
	texHundleEnemy_ = TextureManager::Load("enemy.png");
	enemyModel_ = Model::Create();
	for (int i = 0; i < remainEnemy; i++)
	{
		enemyWorldTransform_[i].scale_ = {0.5f, 0.5f, 0.5f};
		enemyWorldTransform_[i].Initialize();
	}	

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

	//サウンドデータの読み込み
	soundDataHandleTitleBGM_ = audio_->LoadWave("Audio/Ring05.wav");
	soundDataHandleGamePlayBGM_ = audio_->LoadWave("Audio/Ring08.wav");
	soundDataHandleGameOverBGM_ = audio_->LoadWave("Audio/Ring09.wav");
	soundDataHandleEnemyHitSE_ = audio_->LoadWave("Audio/chord.wav");
	soundDataHandlePlayerHitSE_ = audio_->LoadWave("Audio/tada.wav");

	//タイトルBGM再生
	voiceHandleBGM_ = audio_->PlayWave(soundDataHandleTitleBGM_, true);

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
	for (int i = 0; i < remainBeam; i++)
	{
		beamWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    beamWorldTransform_[i].scale_,
			beamWorldTransform_[i].rotation_,
		    beamWorldTransform_[i].translation_);
		// 変換行列をバッファに転送
		beamWorldTransform_[i].TransferMatrix();
	}
}

void GameScene::BeamBorn()
{
	for (int i = 0; i < remainBeam; i++)
	{
		if (beamCoolTime_ == 0)
		{
			if (input_->TriggerKey(DIK_SPACE) && !beamFlag_[i])
			{
				beamFlag_[i] = true;
				beamWorldTransform_[i].translation_.x = playerWorldTransform_.translation_.x;
				beamWorldTransform_[i].translation_.z = playerWorldTransform_.translation_.z;
				beamCoolTime_ = 1;
				break;
			}
		}
		else
		{
			//クールタイムが1以上
			//90を超えると再び発射が可能
			beamCoolTime_++;
			if (beamCoolTime_ > 90)
			{
				beamCoolTime_ = 0;
			}
		}		
	}
}

void GameScene::BeamMove()
{
	for (int i = 0; i < remainBeam; i++)
	{
		if (beamFlag_[i])
		{
			beamWorldTransform_[i].translation_.z += 0.5f;
			beamWorldTransform_[i].rotation_.x += 0.1f;
		}

		if (beamWorldTransform_[i].translation_.z >= 40.0f)
		{
			beamFlag_[i] = false;
		}
	}
}

void GameScene::EnemyUpdate()
{
	EnemyBorn();
	EnemyMove();
	EnemyDelete();

	for (int i = 0; i < remainEnemy; i++)
	{
		// 変換行列を更新
			enemyWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    enemyWorldTransform_[i].scale_, enemyWorldTransform_[i].rotation_,
		    enemyWorldTransform_[i].translation_);
		// 変換行列をバッファに転送
		    enemyWorldTransform_[i].TransferMatrix();
	}	
}

void GameScene::EnemyBorn()
{
	if (rand() % 10 == 0)
	{
		for (int i = 0; i < remainEnemy; i++) 
		{
			if (!enemyAlive_[i])
			{
				// 乱数でX座標の指定
				int x = rand() % 80;
				float x2 = (float)x / 10 - 4;
				enemyAlive_[i] = true;
				enemyWorldTransform_[i].translation_.x = x2;
				enemyWorldTransform_[i].translation_.y = 0;
				enemyWorldTransform_[i].translation_.z = 40;
				//X移動成分初期値の設定
				if (rand() % 2 == 0)
				{
					enemyAmplitude[i] = 0.1f;
				}
				else
				{
					enemyAmplitude[i] = -0.1f;
				}

				break;
			}
		}
	}
}

void GameScene::EnemyMove()
{
	for (int i = 0; i < remainEnemy; i++)
	{
		if (enemyAlive_[i] == 1)
		{
			enemyWorldTransform_[i].translation_.z -= 0.2f;
			enemyWorldTransform_[i].rotation_.z += 0.2f;
			enemyWorldTransform_[i].translation_.x += enemyAmplitude[i];
			if (enemyWorldTransform_[i].translation_.x > 4)
			{
				enemyAmplitude[i] *= -1;
			}
			else if (enemyWorldTransform_[i].translation_.x < -4)
			{
				enemyAmplitude[i] *= -1;
			}

			if (enemyWorldTransform_[i].translation_.z < -5)
			{
				enemyAlive_[i] = false;
			}
		}
	}
}

void GameScene::EnemyDelete()
{
	for (int i = 0; i < remainEnemy; i++)
	{
		if (enemyAlive_[i] == 2)
		{
			//移動
			enemyWorldTransform_[i].translation_.y += enemyJampSpd_[i];
			//速度を減らす
			enemyJampSpd_[i] -= 0.1f;
			//斜め移動
			enemyWorldTransform_[i].translation_.x += enemyAmplitude[i] * 3;
			//下に落ちると消滅
			if (enemyWorldTransform_[i].translation_.y < -3)
			{
				enemyAlive_[i] = false;
			}
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
	for (int i = 0; i < remainEnemy; i++)
	{
		// 敵が生きていれば
		if (enemyAlive_[i])
		{
			// 差を求める
			float dx =
			    abs(playerWorldTransform_.translation_.x - enemyWorldTransform_[i].translation_.x);
			float dz =
			    abs(playerWorldTransform_.translation_.z - enemyWorldTransform_[i].translation_.z);

			// 衝突したら
			if (dx < 1 && dz < 1)
			{
				if (playerLife_ > 0)
				{
					playerLife_ -= 1;
				}
				audio_->PlayWave(soundDataHandlePlayerHitSE_);
				enemyAlive_[i] = false;
			}
		}
	}
}

void GameScene::CollisionBtoE()
{
	for (int i = 0; i < remainEnemy; i++)
	{
		for (int j = 0; j < remainBeam; j++)
		{
			//弾が存在かつ敵が生きていれば
			if (enemyAlive_[i] == 1 && beamFlag_[j])
			{
				// 差を求める
				float dx = abs(
				    beamWorldTransform_[j].translation_.x - enemyWorldTransform_[i].translation_.x);
				float dz = abs(
				    beamWorldTransform_[j].translation_.z - enemyWorldTransform_[i].translation_.z);

				// 衝突したら
				if (dx < 1 && dz < 1)
				{
					gameScore_ += 10;
					audio_->PlayWave(soundDataHandleEnemyHitSE_);
					enemyJampSpd_[i] = 1;
					enemyAlive_[i] = 2;
					beamFlag_[j] = false;
				}
			}
		}
	}
}

void GameScene::TitleUpdate()
{
	gameTimer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		GamePlayStart();
		//BGM切り替え
		audio_->StopWave(voiceHandleBGM_);//現在のBGMを停止
		voiceHandleBGM_ = audio_->PlayWave(soundDataHandleGamePlayBGM_, true);
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
	playerWorldTransform_.translation_.x = 0;
	for (int i = 0; i < remainBeam; i++)
	{
		beamFlag_[i] = false;
	}	
	for (int i = 0; i < remainEnemy; i++)
	{
		enemyAlive_[i] = false;
	}
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
	//床のスクロール処理
	StageUpdate();

	if (playerLife_ < 1)
	{
		audio_->StopWave(voiceHandleBGM_);
		voiceHandleBGM_ = audio_->PlayWave(soundDataHandleGameOverBGM_, true);
		scene = GAMEOVER_;
	}
}

void GameScene::GamePlayDraw3D()
{
	// 床
	for (int i = 0; i < stageVal; i++)
	{
		stageModel_->Draw(stageWorldTransform_[i], viewProjection_, texHundleStage_);
	}
	// プレイヤー
	playerModel_->Draw(playerWorldTransform_, viewProjection_, texHundlePlayer_);
	
	if (scene == GAMEPLAY_)
	{
		// ビーム
		for (int i = 0; i < remainBeam; i++)
		{
			if (beamFlag_[i])
			{
				beamModel_->Draw(beamWorldTransform_[i], viewProjection_, texHundleBeam_);
			}
		}
		// 敵
		for (int i = 0; i < remainEnemy; i++)
		{
			if (!(!enemyAlive_[i]))
			{
				enemyModel_->Draw(enemyWorldTransform_[i], viewProjection_, texHundleEnemy_);
			}
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
		audio_->StopWave(voiceHandleBGM_);
		voiceHandleBGM_ = audio_->PlayWave(soundDataHandleTitleBGM_, true);
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

void GameScene::StageUpdate()
{
	for (int i = 0; i < stageVal; i++)
	{
		//手前に移動
		stageWorldTransform_[i].translation_.z -= 0.1f;
		//端まで来たら奥へ戻る
		if (stageWorldTransform_[i].translation_.z < -5)
		{
			stageWorldTransform_[i].translation_.z += 40;
		}
		//変換行列を更新
		stageWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    stageWorldTransform_[i].scale_,
			stageWorldTransform_[i].rotation_,
		    stageWorldTransform_[i].translation_);
		// 変換行列を定数バッファに転送
		stageWorldTransform_[i].TransferMatrix();
	}
}