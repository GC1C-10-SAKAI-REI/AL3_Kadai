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
#include "DebugText.h"

class GamePlay
{
private:
	ViewProjection view_;

public:
	//�R���X�g���N�^
	GamePlay();

	//�f�X�g���N�^
	~GamePlay();

	//������
	void Initialize();

	//�X�V
	void Update();

	//2D�w�i�`��
	void Draw2Far();

	//3D�`��
	void Draw3D();

	//2D�O�i�`��
	void Draw2DNear();
};