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

void Enemy::Update()
{
	//変換行列を更新
	enemyWorldTransform_.matWorld_ = MakeAffineMatrix(
		enemyWorldTransform_.scale_,
		enemyWorldTransform_.rotation_,
		enemyWorldTransform_.translation_);
	//変換行列を定数バッファに転送
	enemyWorldTransform_.TransferMatrix();
}

void Enemy::Draw3D()
{
	enemyModel_->Draw(enemyWorldTransform_,view_,enemyTexHundle_);
}