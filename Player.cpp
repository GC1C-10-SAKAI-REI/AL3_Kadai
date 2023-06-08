#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
	delete playerModel_;
}

void Player::Initialize(ViewProjection viewProjection)
{
	//メンバー変数に代入
	viewProjection_ = viewProjection;

	playerTexHundle_ = TextureManager::Load("player.png");
	playerModel_ = Model::Create();
	playerWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	playerWorldTransform_.Initialize();
}

void Player::Update()
{
	//変換行列を更新
	playerWorldTransform_.matWorld_ = MakeAffineMatrix(
	    playerWorldTransform_.scale_,
		playerWorldTransform_.rotation_,
	    playerWorldTransform_.translation_);

	//変換行列を定数バッファに転送
	playerWorldTransform_.TransferMatrix();
}

void Player::Draw3D()
{
	playerModel_->Draw(playerWorldTransform_, viewProjection_, playerTexHundle_);
}