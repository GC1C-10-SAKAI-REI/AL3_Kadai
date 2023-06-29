#include "GamePlay.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{
	// 各クラスの削除
	delete stage_;  // ステージ
	delete player_; // プレイヤー
	delete beam_;   // ビーム
	// 敵
	for (Enemy* enemy : enemys_)
	{
		delete enemy;
	}
}

void GamePlay::Initialize(ViewProjection view)
{
	// デバッグテキスト
	debugText_ = DebugText::GetInstance();

	// ビュープロジェクションの初期化
	view_ = view;

	// 各クラスの生成
	stage_ = new Stage();   // ステージ
	player_ = new Player(); // プレイヤー
	// ビーム
	for (int i = 0; i < magazine_; i++)
	{
		beams_[i] = new Beam();
	}
	// 敵(生成の際はインスタンスが出来てないので普通のfor文を使う)
	for (int i = 0; i < remainEnemys_; i++)
	{
		enemys_[i] = new Enemy(); 
	}

	// 各クラスの初期化
	// ステージ
	stage_->Initialize(view_);
	// プレイヤー
	player_->Initialize(view_);
	// ビーム
	for (Beam* beam : beams_)
	{
		beam->Initialize(view_, player_);
	}	
	// 敵
	for (Enemy* enemy : enemys_)
	{
		enemy->Initialize(view_);
	}
	// デバッグテキスト
	debugText_->Initialize();
}

void GamePlay::Start()
{
	//プレイヤー
	player_->Start();
	//ビーム
	beam_->Start();
	//敵
	for (Enemy *enemy : enemys_)
	{
		enemy->Start();
	}
	//プレイヤーライフ
	playerLife_ = 3;
	//ゲームスコア
	gameScore_ = 0;
}

void GamePlay::Update(Scene& scene)
{
	// 各当たり判定
	CollisionPtoE();
	CollisionBtoE();

	// 各クラスの更新
	// ステージ
	stage_->Update();
	// プレイヤー
	player_->Update();
	// 弾
	beam_->Update();
	// 敵
	for (Enemy* enemy : enemys_)
	{
		enemy->Update();
	}	
	//ゲームオーバー遷移条件
	if (playerLife_ < 1)
	{
		scene = GAMEOVER;
	}
}

void GamePlay::Draw2Far()
{
	// 背景の描画
	stage_->Draw2DFar();
}

void GamePlay::Draw3D()
{
	// ステージ
	stage_->Draw3D();
	// 自機
	if (playerLife_ > 0)
	{
		player_->Draw3D();
	}
	// 弾
	beam_->Draw3D();
	// 敵
	for (Enemy *enemy : enemys_)
	{
		enemy->Draw3D();
	}
}

void GamePlay::Draw2DNear()
{
	// ゲームスコア
	char score[100];
	sprintf_s(score, "SCORE : %d", gameScore_);
	debugText_->Print(score, 200, 10, 2);
	// プレイヤーライフ
	char life[100];
	sprintf_s(life, "LIFE : %d", playerLife_);
	debugText_->Print(life, 840, 10, 2);

	// デバッグテキストを表示
	debugText_->DrawAll();
}

void GamePlay::CollisionPtoE()
{
	for (Enemy *enemy : enemys_)
	{
		// 敵が存在すれば
		if (enemy->GetFlag() == 1)
		{
			// 差を求める
			float dx = abs(player_->GetX() - enemy->GetX());
			float dz = abs(player_->GetZ() - enemy->GetZ());

			// 衝突したら
			if (dx < 1 && dz < 1)
			{
				enemy->Hit();
				if (playerLife_ > 0)
				{
					playerLife_--;
				}
			}
		}
	}
}

void GamePlay::CollisionBtoE()
{
	for (Enemy *enemy : enemys_)
	{
		// 敵が生きていれば
		if (enemy->GetFlag() && beam_->GetFlag()) {
			// 差を求める
			float dx = abs(beam_->GetX() - enemy->GetX());
			float dz = abs(beam_->GetZ() - enemy->GetZ());

			// 衝突したら
			if (dx < 1 && dz < 1)
			{
				gameScore_ += 10;
				enemy->Hit();
				beam_->Hit();
			}
		}
	}
}