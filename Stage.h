#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"

class Stage
{
private:
	//ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	//BG(スプライト)
	uint32_t BGTexHundle_ = 0;
	Sprite *BGSprite_ = nullptr;

	//ステージ
	uint32_t stageTexHundle_ = 0;
	Model *stageModel_ = nullptr;
	WorldTransform stageWorldTransform_;

public:
	//コンストラクタ
	Stage();

	//デストラクタ
	~Stage();

	//初期化
	void Initialize(ViewProjection viewProjection);

	//更新
	void Update();

	//2D背景描画
	void Draw2DFar();

	//3D表示
	void Draw3D();
};