#include "Beam.h"

Beam::Beam()
{

}

Beam::~Beam()
{
	delete beamModel_;
}

void Beam::Initialize(ViewProjection viewProjection,Player *player)
{
	//メンバー変数に代入
	viewProjection_ = viewProjection;

	//プレイヤー
	player_ = player;

	//弾
	beamTexHundle_ = TextureManager::Load("beam.png");
	beamModel_ = Model::Create();
	beamWorldTransform_.scale_ = {0.3f, 0.3f, 0.3f};
	beamWorldTransform_.Initialize();
	// インプットクラス
	input_ = Input::GetInstance();
}

void Beam::Start()
{
	aliveFlag_ = 0;
}

void Beam::Update()
{
	Born();
	 
	Move();

	// 変換行列を更新
	beamWorldTransform_.matWorld_ = MakeAffineMatrix(
	    beamWorldTransform_.scale_,
		beamWorldTransform_.rotation_,
	    beamWorldTransform_.translation_);
	// 変換行列を定数バッファに転送
	beamWorldTransform_.TransferMatrix();
}

void Beam::Born()
{
	if (input_->TriggerKey(DIK_SPACE) && !aliveFlag_)
	{
		aliveFlag_ = true;
		beamWorldTransform_.translation_.x = player_->GetX();
		beamWorldTransform_.translation_.z = player_->GetZ();
	}
}

void Beam::Move()
{
	if (aliveFlag_)
	{
		beamWorldTransform_.translation_.z += 0.5f;
		beamWorldTransform_.rotation_.x += 0.1f;
	}

	if (beamWorldTransform_.translation_.z >= 40.0f)
	{
		aliveFlag_ = false;
	}
}


void Beam::Draw3D()
{
	if (aliveFlag_)
	{
		beamModel_->Draw(beamWorldTransform_,viewProjection_,beamTexHundle_);
	}
}