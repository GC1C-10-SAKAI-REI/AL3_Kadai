#include "Title.h"

Title::Title()
{

}

Title::~Title()
{
	// タイトル
	delete titleSprite_;
	//ヒットエンターキー
	delete hitEnterSprite_;
	//列挙体
	delete sEnum_;
}

void Title::Initialize()
{
	//タイトル
	titleTexHundle_ = TextureManager::Load("title.png");
	titleSprite_ = Sprite::Create(titleTexHundle_, {0, 0});
	//ヒットエンターキー
	hitEnterTexHundle_ = TextureManager::Load("enter.png");
	hitEnterSprite_ = Sprite::Create(hitEnterTexHundle_, {400, 360});
	//サウンドデータの読み込み
	audio_ = Audio::GetInstance();
	bgmSoundHundle_ = audio_->LoadWave("Audio/Ring05.wav");

	// インプットクラス
	input_ = Input::GetInstance();
}

void Title::BGMPlay()
{
	//BGMを再生
	bgmPlayHundle_ = audio_->PlayWave(bgmSoundHundle_, true);
}

void Title::Update(Scene &scene)
{
	timer_++;

	if (input_->TriggerKey(DIK_RETURN))
	{
		//現在のBGMを停止
		audio_->StopWave(bgmPlayHundle_);
		//ゲームプレイへ移行
		scene = GAMEPLAY;
	}
	else
	{
		scene = TITLE;
	}
}

void Title::Draw2DNear()
{
	// タイトル
	titleSprite_->Draw();
	//ヒットエンターキー
	if (timer_ % 40 >= 20)
	{
		hitEnterSprite_->Draw();
	}
}