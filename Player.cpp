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

	//プレイヤー
	playerTexHundle_ = TextureManager::Load("player.png");
	playerModel_ = Model::Create();
	playerWorldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	playerWorldTransform_.Initialize();
	//インプットクラス
	input_ = Input::GetInstance();
}

void Player::Start()
{
	playerWorldTransform_.translation_.x = 0;
}

void Player::Update()
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
	//端にいったら止める
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

	//変換行列を定数バッファに転送
	playerWorldTransform_.TransferMatrix();
}

void Player::Draw3D()
{
	playerModel_->Draw(playerWorldTransform_, viewProjection_, playerTexHundle_);
}