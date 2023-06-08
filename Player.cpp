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

}

void Player::Draw3D()
{
	playerModel_->Draw(playerWorldTransform_, viewProjection_, playerTexHundle_);
}