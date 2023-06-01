#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Stage
{
public:
	//�R���X�g���N�^
	Stage();

	//�f�X�g���N�^
	~Stage();

	//������
	void Initialize();

	//�X�V
	void Update();

	//2D�w�i�`��
	void Draw2DFar();
};