#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	delete enemyModel_;
}

void Enemy::Initialize(ViewProjection view)
{
	//メンバー変数に代入
	view_ = view;

	//敵
	enemyTexHundle_ = TextureManager::Load("enemy.png");
	enemyModel_ = Model::Create();
	enemyWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	enemyWorldTransform_.Initialize();
}

void Enemy::Start()
{
	aliveFlag_ = 0;
	// 乱数でX座標の指定
	int x = rand() % 80;
	float x2 = (float)x / 10 - 4;
	enemyWorldTransform_.translation_.x = x2;
	enemyWorldTransform_.translation_.z = 40;
}

void Enemy::Update()
{
	//生成
	Born();
	//移動
	Move();
	//
	EnemyDelete();

	//変換行列を更新
	enemyWorldTransform_.matWorld_ = MakeAffineMatrix(
		enemyWorldTransform_.scale_,
		enemyWorldTransform_.rotation_,
		enemyWorldTransform_.translation_);
	//変換行列を定数バッファに転送
	enemyWorldTransform_.TransferMatrix();
}

void Enemy::Born()
{
	if (rand() % 10 == 0)
	{
		if (aliveFlag_ == 0)
		{
			aliveFlag_ = true;
			// 乱数でX座標の指定
			int x = rand() % 80;
			float x2 = (float)x / 10 - 4;

			enemyWorldTransform_.translation_.x = x2;
			enemyWorldTransform_.translation_.y = 0;
			enemyWorldTransform_.translation_.z = 40;

			//Born内でX成分の抽選
			if (rand() % 2 == 0)
			{
				enemySpdX_ = 0.1f;
			}
			else
			{
				enemySpdX_ = -0.1f;
			}
		}
	}
}

void Enemy::Move() 
{
	if (aliveFlag_ == 1)
	{
		//基本の移動(前進)
		enemyWorldTransform_.translation_.z -= 0.2f;
		enemyWorldTransform_.rotation_.z += 0.2f;
		//斜め移動
		enemyWorldTransform_.translation_.x += enemySpdX_;
		//端にぶつかったら反転
		if (enemyWorldTransform_.translation_.x > 4)
		{
			enemySpdX_ *= -1;
		}
		else if(enemyWorldTransform_.translation_.x < -4)
		{
			enemySpdX_ *= -1;
		}

		if (enemyWorldTransform_.translation_.z < -5)
		{
			aliveFlag_ = false;
		}
	}
}

void Enemy::EnemyDelete()
{
	if (aliveFlag_ == 2)
	{
		// 移動
		enemyWorldTransform_.translation_.y += jampSpd_;
		// 速度を減らす
		jampSpd_ -= 0.1f;
		// 斜め移動
		enemyWorldTransform_.translation_.x += enemySpdX_ * 3;
		// 下に落ちると消滅
		if (enemyWorldTransform_.translation_.y < -3)
		{
			aliveFlag_ = false;
		}
	}
}

void Enemy::Draw3D()
{
	enemyModel_->Draw(enemyWorldTransform_,view_,enemyTexHundle_);
}