#include "Stage.h"

Stage::Stage()
{

}

Stage::~Stage()
{
	delete BGSprite_;	//BG
}

void Stage::Initialize() 
{ 
	BGTexHundle_ = TextureManager::Load("bg.jpg"); 
	BGSprite_ = Sprite::Create(BGTexHundle_, {0, 0});
}

void Stage::Update()
{

}

void Stage::Draw2DFar()
{
	BGSprite_->Draw();
}