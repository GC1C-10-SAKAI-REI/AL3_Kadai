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

//ゲームシーン
class GameScene
{
private://メンバ変数
	DirectXCommon *dxCommon_ = nullptr;
	Input *input_ = nullptr;
	Audio *audio_ = nullptr;

	// ゲームシーン用
	//ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	// 各クラス
	Stage *stage_ = nullptr;	// ステージ
	Player *player_ = nullptr;	//プレイヤー	
	Beam *beam_ = nullptr;		//弾
	Enemy *enemy_ = nullptr;	//敵

public://メンバ関数	
	//コンストクラタ	
	GameScene();
	
	//デストラクタ	
	~GameScene();
	
	//初期化	
	void Initialize();
	
	//更新処理
	void Update();
	
	//描画処理
	void Draw();
};