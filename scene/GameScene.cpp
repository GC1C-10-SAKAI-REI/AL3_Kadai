#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene(){}

GameScene::~GameScene()
{
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHundle_ = TextureManager::Load("sample.png");
	modelHundle_ = TextureManager::Load("uvChecker.png");
	//サウンドデータの読み込み
	soundDataHundle_ = audio_->LoadWave("fanfare.wav");
	//スプライトの生成
	sprite_ = Sprite::Create(textureHundle_, {45, 50});
	//3Dモデルの生成
	model_ = Model::Create();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//音声再生
	voiceHundle_ = audio_->PlayWave(soundDataHundle_, true);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update()
{
	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	//座標を{1,1}移動
	position.x += 1.0f;
	position.y += 1.0f;
	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	//スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_SPACE))
	{
		//音声停止
		audio_->StopWave(voiceHundle_);
	}
	//ウィンドウの作成
	ImGui::Begin("Debug1");
	// デバッグテキストの表示
	ImGui::Text("Sakai Rei %d.%d.%d", 2023, 04, 20);
	//float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	//float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
	//デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();
	//デバッグカメラの更新
	debugCamera_->Update();
}

void GameScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	//sprite_->Draw();
	//ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {10,10,0,},{1.0f,0.0f,0.0f,1.0f});

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), modelHundle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}