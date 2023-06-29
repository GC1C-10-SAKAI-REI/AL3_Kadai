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
	delete enemy_;  // 敵
}

void GamePlay::Initialize(ViewProjection view)
{
	// デバッグテキスト
	debugText_ = DebugText::GetInstance();

	//ビュープロジェクションの初期化
	view_ = view;

	// 各クラスの生成
	stage_ = new Stage();   // ステージ
	player_ = new Player(); // プレイヤー
	beam_ = new Beam();     // ビーム
	for (int i = 0; i < remainEnemys_; i++)
	{
		enemys_[i] = new Enemy(); // 敵
	}

	// 各クラスの初期化
	// ステージ
	stage_->Initialize(view_);
	// プレイヤー
	player_->Initialize(view_);
	// ビーム
	beam_->Initialize(view_, player_);
	// 敵
	for (int i = 0; i < remainEnemys_; i++)
	{
		enemys_[i]->Initialize(view_);
	}
	// デバッグテキスト
	debugText_->Initialize();
}

void GamePlay::Start()
{
	player_->Start();
	beam_->Start();
	enemy_->Start();
	playerLife_ = 3;
	gameScore_ = 0;
}

void GamePlay::Update(Scene& scene)
{
	// 当たり判定
	CollisionPtoE();
	CollisionBtoE();

	// 各クラスの更新
	stage_->Update();  // ステージ
	player_->Update(); // プレイヤー
	beam_->Update();   // 弾
	enemy_->Update();  // 敵

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
	enemy_->Draw3D();
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
	// 敵が存在すれば
	if (enemy_->GetFlag() == 1)
	{
		// 差を求める
		float dx = abs(player_->GetX() - enemy_->GetX());
		float dz = abs(player_->GetZ() - enemy_->GetZ());

		// 衝突したら
		if (dx < 1 && dz < 1)
		{
			enemy_->Hit();
			if (playerLife_ > 0)
			{
				playerLife_--;
			}
		}
	}
}

void GamePlay::CollisionBtoE()
{
	// 敵が生きていれば
	if (enemy_->GetFlag() && beam_->GetFlag())
	{
		// 差を求める
		float dx = abs(beam_->GetX() - enemy_->GetX());
		float dz = abs(beam_->GetZ() - enemy_->GetZ());

		// 衝突したら
		if (dx < 1 && dz < 1)
		{
			gameScore_ += 10;
			enemy_->Hit();
			beam_->Hit();
		}
	}
}