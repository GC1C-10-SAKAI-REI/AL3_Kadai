#include "Stage.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	delete BGSprite_;	//BG
	delete stageModel_;	//ステージ
}

void Stage::Initialize(ViewProjection viewProjection)
{
	//メンバー変数に代入
	viewProjection_ = viewProjection;

	//BG
	BGTexHundle_ = TextureManager::Load("bg.jpg"); 
	BGSprite_ = Sprite::Create(BGTexHundle_, {0, 0});

	//ステージ
	stageTexHundle_ = TextureManager::Load("stage.jpg");
	stageModel_ = Model::Create();
	stageWorldTransform_.Initialize();

	// ステージの位置を変更
	stageWorldTransform_.translation_ = {0, -1.5f, 0};
	stageWorldTransform_.scale_ = {4.5f, 1, 40};
	// 変換行列を更新
	stageWorldTransform_.matWorld_ = MakeAffineMatrix(
	    stageWorldTransform_.scale_, stageWorldTransform_.rotation_,
	    stageWorldTransform_.translation_);
	// 変換行列を定数バッファに転送
	stageWorldTransform_.TransferMatrix();
}

void Stage::Update()
{

}

void Stage::Draw2DFar()
{
	//BG
	BGSprite_->Draw();
}

void Stage::Draw3D()
{
	//ステージ
	stageModel_->Draw(stageWorldTransform_, viewProjection_, stageTexHundle_);
}