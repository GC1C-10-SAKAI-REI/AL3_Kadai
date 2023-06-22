#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Title
{
public:
	// コンストラクタ
	Title();

	// デストラクタ
	~Title();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 2D前景描画
	void Draw2DNear();
};