#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "Input.h"

class Player
{
private:
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	//プレイヤー
	uint32_t playerTexHundle_ = 0;
	Model *playerModel_ = nullptr;
	WorldTransform playerWorldTransform_;

	Input* input_ = nullptr;

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化
	void Initialize(ViewProjection viewProjection);

	// 2周目以降の初期化処理
	void Start();

	//更新
	void Update();

	//2D背景描画
	void Draw3D();

	//X座標の取得
	float GetX() { return playerWorldTransform_.translation_.x; }
	//Z座標の取得
	float GetZ() { return playerWorldTransform_.translation_.z; }
};