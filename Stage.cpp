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