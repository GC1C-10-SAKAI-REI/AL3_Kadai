#include "GameOver.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	//ゲームオーバー
	delete gameoverSprite_;
	//エンターキー
	delete hitEnterSprite_;
	//
	delete sEnum;
}

void GameOver::Initialize(ViewProjection view)
{
	//ゲームオーバー
	gameoverTexHundle_ = TextureManager::Load("gameover.png");
	gameoverSprite_ = Sprite::Create(gameoverTexHundle_, {0, 0});
	//
	hitEnterTexHundle_ = TextureManager::Load("enter.png");
	hitEnterSprite_ = Sprite::Create(hitEnterTexHundle_, {400, 360});

	input_ = Input::GetInstance();
}

void GameOver::Update(Scene& scene)
{
	timer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		scene = TITLE;
	}
	else
	{
		scene_ = GAMEOVER;
	}
}

void GameOver::Draw2DNear()
{
	// タイトル
	gameoverSprite_->Draw();
	// ヒットエンターキー
	if (timer_ % 40 >= 20)
	{
		hitEnterSprite_->Draw();
	}
}