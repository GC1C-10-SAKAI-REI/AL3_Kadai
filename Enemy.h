#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"

class Enemy
{
private:
	ViewProjection view_;

public:
	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	~Enemy();

	//������
	void Initialize(ViewProjection view);

	//�X�V
	void Update();

	//3D�`��
	void Draw3D();
};