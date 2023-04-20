#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHundle_ = 0;//uintは1年で言うint型
	uint32_t modelHundle_ = 0;
	//スプライト
	Sprite *sprite_ = nullptr;
	Model *model_ = nullptr;
	//ワールドトランスフォーム(3Dモデルのアフィン行列)
	WorldTransform worldTransform_;
	//ビュープロジェクション(カメラ)
	ViewProjection viewProjection_;
	//サウンドデータハンドル
	uint32_t soundDataHundle_ = 0;
	//音声再生ハンドル
	uint32_t voiceHundle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
