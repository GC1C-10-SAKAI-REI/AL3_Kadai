#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "SceneEnum.h"

class GameOver : public SceneEnum
{
private:
	// ゲームオーバー
	uint32_t gameoverTexHundle_ = 0;
	Sprite* gameoverSprite_ = nullptr;
	// ヒットエンターキー
	uint32_t hitEnterTexHundle_ = 0;
	Sprite* hitEnterSprite_ = nullptr;
	// シーン管理用列挙体クラス
	SceneEnum* sEnum = nullptr;
	//入力クラス
	Input* input_ = nullptr;

	// エンター点滅用
	int timer_ = 0;

public:
	// コンストラクタ
	GameOver();

	// デストラクタ
	~GameOver();

	// 初期化
	void Initialize(ViewProjection view);

	// 更新
	void Update(Scene& scene);

	// 2D前景描画
	void Draw2DNear();
};