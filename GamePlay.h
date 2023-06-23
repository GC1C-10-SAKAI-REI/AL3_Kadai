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

	// 各クラス
	Stage *stage_ = nullptr;   // ステージ
	Player *player_ = nullptr; // プレイヤー
	Beam *beam_ = nullptr;     // 弾
	Enemy *enemy_ = nullptr;   // 敵

	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	int gameScore_ = 0;  // ゲームスコア
	int playerLife_ = 3; // プレイヤーの残機

public:
	//コンストラクタ
	GamePlay();

	//デストラクタ
	~GamePlay();

	//初期化
	void Initialize(ViewProjection view);

	//更新
	void Update();

	//2D背景描画
	void Draw2Far();

	//3D描画
	void Draw3D();

	//2D前景描画
	void Draw2DNear();

	// 衝突判定(自機と敵)
	void CollisionPtoE();

	// 衝突判定(ビームと敵)
	void CollisionBtoE();
};