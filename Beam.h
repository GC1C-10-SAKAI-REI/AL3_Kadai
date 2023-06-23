#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "Input.h"
#include "Player.h"

class Beam
{
private:
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	//ビーム
	uint32_t beamTexHundle_ = 0;
	Model *beamModel_ = nullptr;
	WorldTransform beamWorldTransform_;

	//インプットクラス
	Input *input_ = nullptr;
	//存在フラグ
	int aliveFlag_ = 0;

	//プレイヤー
	Player *player_ = nullptr;

public:
	// コンストラクタ
	Beam();

	// デストラクタ
	~Beam();

	// 初期化
	void Initialize(ViewProjection viewProjection, Player *player);

	//
	void Start();

	// 更新
	void Update();

	//移動
	void Move();

	//発生(発射)
	void Born();

	// 3D描画
	void Draw3D();

	// 衝突処理
	void Hit() { aliveFlag_ = 0; };

	//弾の存在フラグのゲッター
	int GetFlag() { return aliveFlag_; }

	// X座標の獲得
	float GetX() { return beamWorldTransform_.translation_.x; }
	// Z座標の取得
	float GetZ() { return beamWorldTransform_.translation_.z; }
};