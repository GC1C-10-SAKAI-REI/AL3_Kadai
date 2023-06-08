#include "Beam.h"

Beam::Beam()
{

}

Beam::~Beam()
{
	delete beamModel_;
}

void Beam::Initialize(ViewProjection viewProjection)
{
	//メンバー変数に代入
	viewProjection_ = viewProjection;

	//弾
	beamTexHundle_ = TextureManager::Load("beam.png");
	beamModel_ = Model::Create();
	beamWorldTransform_.scale_ = {0.3f, 0.3f, 0.3f};
	beamWorldTransform_.Initialize();
}

void Beam::Update()
{
	// 変換行列を更新
	beamWorldTransform_.matWorld_ = MakeAffineMatrix(
	    beamWorldTransform_.scale_,
		beamWorldTransform_.rotation_,
	    beamWorldTransform_.translation_);
	// 変換行列を定数バッファに転送
	beamWorldTransform_.TransferMatrix();
}

void Beam::Draw3D()
{
	beamModel_->Draw(beamWorldTransform_,viewProjection_,beamTexHundle_);
}