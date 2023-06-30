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
	//斜め移動の際のX成分
	float enemySpdX_ = 0.0f;

public:
	//コンストラクタ
	Enemy();

	//デストラクタ
	~Enemy();

	//初期化
	void Initialize(ViewProjection view);

	// 2周目以降の初期化処理
	void Start();

	//更新
	void Update();

	//発生
	void Born();

	//移動
	void Move();

	//3D描画
	void Draw3D();

	//衝突処理
	void Hit() { aliveFlag_ = 0; };

	//生存フラグ獲得
	int GetFlag() { return aliveFlag_; }

	//X座標の獲得
	float GetX() { return enemyWorldTransform_.translation_.x; }
	//Z座標の取得
	float GetZ() { return enemyWorldTransform_.translation_.z; }
};