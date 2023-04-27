#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

//ゲームシーン
class GameScene
{
private://メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// ゲームシーン用
	uint32_t bgTexHundle_ = 0;
	Sprite *spriteBG_ = nullptr;
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	// ステージ
	uint32_t texHundleStage_ = 0;
	Model* stageModel_ = nullptr;
	WorldTransform stageWorldTransform_;

	//プレイヤー
	uint32_t texHundlePlayer_ = 0;
	Model* playerModel_ = nullptr;
	WorldTransform playerWorldTransform_;

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
	void PlayerUpdate();

};