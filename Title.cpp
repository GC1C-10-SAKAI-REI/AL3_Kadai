#include "Title.h"

Title::Title()
{

}

Title::~Title()
{
	// タイトル
	delete titleSprite_;
	delete hitEnterSprite_;
}

void Title::Initialize()
{
	//タイトル
	titleTexHundle_ = TextureManager::Load("title.png");
	titleSprite_ = Sprite::Create(titleTexHundle_, {0, 0});
	//
	hitEnterTexHundle_ = TextureManager::Load("enter.png");
	hitEnterSprite_ = Sprite::Create(hitEnterTexHundle_, {400, 360});
}

void Title::Update()
{

}

void Title::Draw2DNear()
{
	// タイトル
	titleSprite_->Draw();
	//
	hitEnterSprite_->Draw();
}