#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <time.h>

//ゲームシーン
class GameScene
{
private://メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	// ゲームシーン用
	uint32_t bgTexHundle_ = 0;
	Sprite *spriteBG_ = nullptr;

	// ステージ
	uint32_t texHundleStage_ = 0;
	Model* stageModel_ = nullptr;
	WorldTransform stageWorldTransform_;

	//プレイヤー
	uint32_t texHundlePlayer_ = 0;
	Model* playerModel_ = nullptr;
	WorldTransform playerWorldTransform_;

	// ビーム
	uint32_t texHundleBeam_ = 0;
	Model* beamModel_ = nullptr;
	WorldTransform beamWorldTransform_;
	//ビーム管理フラグ
	bool beamFlag_ = false;

	//敵
	uint32_t texHundleEnemy_ = 0;
	Model* enemyModel_ = nullptr;
	WorldTransform enemyWorldTransform_;
	bool enemyAlive = false;

public://メンバ関数
	//コンストラクタ
	GameScene();
	//デストラクタ
	~GameScene();
	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

private:
	//自機更新
	void PlayerUpdate();
	//ビーム更新
	void BeamUpdate();
	//ビーム発生
	void BeamBorn();
	//ビーム移動
	void BeamMove();
	//敵の更新
	void EnemyUpdate();
	//敵の発生
	void EnemyBorn();
	//敵の移動
	void EnemyMove();
	//衝突判定
	void Collision();
	//衝突判定(自機と敵)
	void CollisionPtoE();
	//衝突判定(ビームと敵)
	//void CollisionBtoE();
};