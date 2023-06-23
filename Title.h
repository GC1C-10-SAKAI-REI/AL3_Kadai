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

class Title : public SceneEnum
{
private:
	//タイトル
	uint32_t titleTexHundle_ = 0;
	Sprite *titleSprite_ = nullptr;
	//ヒットエンターキー
	uint32_t hitEnterTexHundle_ = 0;
	Sprite *hitEnterSprite_ = nullptr;
	//
	SceneEnum *sEnum = nullptr;

	Input* input_ = nullptr;

	//エンター点滅用
	int timer_ = 0;

public:
	// コンストラクタ
	Title();

	// デストラクタ
	~Title();

	// 初期化
	void Initialize();

	// 更新
	void Update(Scene &scene);

	// 2D前景描画
	void Draw2DNear();
};