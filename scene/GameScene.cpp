#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

//コンストラクタ
GameScene::GameScene()
{

}

//デストラクタ
GameScene::~GameScene()
{
	//各クラスの削除
	delete stage_;	//ステージ
	delete player_;	//プレイヤー
	delete beam_;	//ビーム
	delete enemy_;	//敵
}

//初期化
void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ビュープロジェクションの初期化
	viewProjection_.translation_.y = 1;
	viewProjection_.translation_.z = -6;
	viewProjection_.Initialize();

	//各クラスの生成
	stage_ = new Stage();	//ステージ
	player_ = new Player();	//プレイヤー
	beam_ = new Beam();		//ビーム
	enemy_ = new Enemy();	//敵

	//各クラスの初期化
	stage_->Initialize(viewProjection_);			//ステージ
	player_->Initialize(viewProjection_);			//プレイヤー
	beam_->Initialize(viewProjection_,player_);		//ビーム
	enemy_->Initialize(viewProjection_);			//敵
}

//更新
void GameScene::Update()
{
	//各クラスの更新
	stage_->Update();	//ステージ
	player_->Update();	//プレイヤー
	beam_->Update();	//弾
	enemy_->Update();
}

//描画
void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	//ここから

	//背景の描画
	stage_->Draw2DFar();

	//ここまで

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここから

	stage_->Draw3D();
	player_->Draw3D();
	beam_->Draw3D();
	enemy_->Draw3D();

	// ここまで

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// ここから

	// ここまで

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}