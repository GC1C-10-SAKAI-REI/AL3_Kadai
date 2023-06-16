#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"

class Enemy
{
private:
	//ビュープロジェクション
	ViewProjection view_;

	//敵
	uint32_t enemyTexHundle_ = 0;
	Model* enemyModel_ = nullptr;
	WorldTransform enemyWorldTransform_;

	//生存フラグ
	int aliveFlag_ = 0;

public:
	//コンストラクタ
	Enemy();

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize(ViewProjection view);

	//更新
	void Update();

	//発生
	void Born();

	//移動
	void Move();

	//3D描画
	void Draw3D();
};