#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Title
{
public:
	// �R���X�g���N�^
	Title();

	// �f�X�g���N�^
	~Title();

	// ������
	void Initialize();

	// �X�V
	void Update();

	// 2D�O�i�`��
	void Draw2DNear();
};