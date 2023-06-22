#include "GamePlay.h"

GamePlay::GamePlay()
{

}

GamePlay::~GamePlay()
{

}

void GamePlay::Initialize()
{
	//ビュープロジェクションの初期化
	view_.translation_.y = 1;
	view_.translation_.z = -6;
	view_.Initialize();
}

void GamePlay::Update()
{

}

void GamePlay::Draw2Far()
{

}

void GamePlay::Draw3D()
{

}

void GamePlay::Draw2DNear()
{

}