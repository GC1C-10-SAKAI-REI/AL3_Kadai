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
	stageTexHundle_ = TextureManager::Load("stage2.jpg");
	stageModel_ = Model::Create();
	for (int i = 0; i < floorNum; i++)
	{
		stageWorldTransform_[i].Initialize();
	}	
	//床の数だけ回す
	for (int i = 0; i < floorNum; i++)
	{
		// ステージの位置を変更
		stageWorldTransform_[i].translation_ = {0, -1.5f, 2.0f * i - 5};
		stageWorldTransform_[i].scale_ = {4.5f, 1, 1};
		// 変換行列を更新
		stageWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    stageWorldTransform_[i].scale_,
			stageWorldTransform_[i].rotation_,
		    stageWorldTransform_[i].translation_);
		// 変換行列を定数バッファに転送
		stageWorldTransform_[i].TransferMatrix();
	}
}

void Stage::Update()
{
	for (int i = 0; i < floorNum; i++)
	{
		// 手前に移動
		stageWorldTransform_[i].translation_.z -= 0.1f;
		// 端まで来たら奥へ戻る
		if (stageWorldTransform_[i].translation_.z < -5)
		{
			stageWorldTransform_[i].translation_.z += 40;
		}
		// 変換行列を更新
		stageWorldTransform_[i].matWorld_ = MakeAffineMatrix(
		    stageWorldTransform_[i].scale_,
			stageWorldTransform_[i].rotation_,
		    stageWorldTransform_[i].translation_);
		// 変換行列を定数バッファに転送
		stageWorldTransform_[i].TransferMatrix();
	}
}

void Stage::Draw2DFar()
{
	//BG
	BGSprite_->Draw();
}

void Stage::Draw3D()
{
	for (int i = 0; i < floorNum; i++)
	{
		// ステージ
		stageModel_->Draw(stageWorldTransform_[i], viewProjection_, stageTexHundle_);
	}	
}