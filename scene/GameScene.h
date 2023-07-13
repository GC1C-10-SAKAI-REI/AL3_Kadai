#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "SceneEnum.h"
#include "Title.h"
#include "GamePlay.h"
#include "GameOver.h"

//ゲームシーン
class GameScene : public SceneEnum
{
private://メンバ変数
	DirectXCommon *dxCommon_ = nullptr;
	Input *input_ = nullptr;
	Audio *audio_ = nullptr;

	// ゲームシーン用
	//ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	//各シーン
	Title *title_ = nullptr;
	GamePlay *gamePlay_ = nullptr;
	GameOver *gameOver_ = nullptr;
	//シーン管理用列挙体クラス
	SceneEnum *sEnum_ = nullptr;

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