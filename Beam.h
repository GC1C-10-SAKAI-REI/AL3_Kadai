#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "Input.h"

class Beam
{
private:
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	//ビーム
	uint32_t beamTexHundle_ = 0;
	Model *beamModel_ = nullptr;
	WorldTransform beamWorldTransform_;

public:
	// コンストラクタ
	Beam();

	// デストラクタ
	~Beam();

	// 初期化
	void Initialize(ViewProjection viewProjection);

	// 更新
	void Update();

	// 2D背景描画
	void Draw3D();
};