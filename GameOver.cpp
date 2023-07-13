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

	// サウンドデータの読み込み
	audio_ = Audio::GetInstance();
	bgmSoundHundle_ = audio_->LoadWave("Audio/Ring09.wav");

	// インプットクラス
	input_ = Input::GetInstance();
}

void GameOver::BGMPlay()
{
	// BGMを再生
	bgmPlayHundle_ = audio_->PlayWave(bgmSoundHundle_, true);
}

void GameOver::Update(Scene& scene)
{
	timer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		// 現在のBGMを停止
		audio_->StopWave(bgmPlayHundle_);
		scene = TITLE;
	}
	else
	{
		scene = GAMEOVER;
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