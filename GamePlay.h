#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Stage.h"
#include "Player.h"
#include "Beam.h"
#include "Enemy.h"
#include "DebugText.h"

class GamePlay
{
private:
	ViewProjection view_;

public:
	//コンストラクタ
	GamePlay();

	//デストラクタ
	~GamePlay();

	//初期化
	void Initialize();

	//更新
	void Update();

	//2D背景描画
	void Draw2Far();

	//3D描画
	void Draw3D();

	//2D前景描画
	void Draw2DNear();
};