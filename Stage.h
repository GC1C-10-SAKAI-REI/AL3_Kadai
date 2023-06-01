#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Stage
{
private:
	//BG(スプライト)
	uint32_t BGTexHundle_ = 0;
	Sprite *BGSprite_ = nullptr;

public:
	//コンストラクタ
	Stage();

	//デストラクタ
	~Stage();

	//初期化
	void Initialize();

	//更新
	void Update();

	//2D背景描画
	void Draw2DFar();
};