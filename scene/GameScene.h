#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugText.h"
#include <time.h>

//シーン列挙体
enum Scene
{ 
	TITLE_,
	GAMEPLAY_,
	GAMEOVER_
};

//ゲームシーン
class GameScene
{
private://メンバ変数
	DirectXCommon *dxCommon_ = nullptr;
	Input *input_ = nullptr;
	Audio *audio_ = nullptr;
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	// ゲームシーン用
	uint32_t bgTexHundle_ = 0;
	Sprite *spriteBG_ = nullptr;

	// ステージ
	uint32_t texHundleStage_ = 0;
	Model *stageModel_ = nullptr;
	WorldTransform stageWorldTransform_;

	//プレイヤー
	uint32_t texHundlePlayer_ = 0;
	Model *playerModel_ = nullptr;
	WorldTransform playerWorldTransform_;
	int playerLife_ = 3;

	// ビーム
	uint32_t texHundleBeam_ = 0;
	Model *beamModel_ = nullptr;
	//残弾数
	static const int remainBeam = 10;
	WorldTransform beamWorldTransform_[remainBeam];
	//ビーム管理フラグ
	bool beamFlag_[remainBeam] = {false};

	//敵
	uint32_t texHundleEnemy_ = 0;
	Model *enemyModel_ = nullptr;
	//敵の数
	static const int remainEnemy = 10;
	WorldTransform enemyWorldTransform_[remainEnemy];
	//死亡フラグ
	bool enemyAlive_[remainEnemy] = {false};

	//デバッグテキスト
	DebugText *debugText_ = nullptr;
	int gameScore_ = 0;	

	//タイトル
	uint32_t texHundleTitle_ = 0;
	Sprite *titleSprite = nullptr;

	//シーン進行案内
	uint32_t texHundleEnter_ = 0;
	Sprite *enterSprite = nullptr;

	//ゲームオーバー
	uint32_t texHundleGameover_ = 0;
	Sprite *gameoverSprite = nullptr;

	//シーン管理用変数
	Scene scene = TITLE_;

	int gameTimer_ = 0;

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
	/*プレイヤー*/
	//自機更新
	void PlayerUpdate();

	/*弾*/
	//ビーム更新
	void BeamUpdate();
	//ビーム発生
	void BeamBorn();
	//ビーム移動
	void BeamMove();

	/*敵*/
	//敵の更新
	void EnemyUpdate();
	//敵の発生
	void EnemyBorn();
	//敵の移動
	void EnemyMove();

	/*当たり判定*/
	//衝突判定
	void Collision();
	//衝突判定(自機と敵)
	void CollisionPtoE();
	//衝突判定(ビームと敵)
	void CollisionBtoE();

	/*シーン関係*/
	//タイトル更新
	void TitleUpdate();
	// タイトル2D
	void TitleDraw2DNear();

	//ゲームプレイ初期化
	void GamePlayStart();
	//ゲームプレイ更新
	void GamePlayUpdate();
	// ゲームプレイ3D表示
	void GamePlayDraw3D();
	// ゲームプレイ背景2D表示
	void GamePlayDraw2DBack();
	// ゲームプレイ近景2D表示
	void GamePlayDraw2DNear();

	// ゲームオーバー更新
	void GameoverUpdate();
	// ゲームオーバー2D
	void GameoverDraw2DNear();
};