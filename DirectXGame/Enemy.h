#pragma once
#include "Model.h"
#include "WorldTransform.h"

class MapChipField;

/// <summary>
/// �G
/// </summary>
class Enemy 
{
public:
	
	Enemy();
	~Enemy();


	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="model">���f��</param>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private:
	// �}�b�v�`�b�v�ɂ��t�B�[���h
	MapChipField* mapChipField_ = nullptr;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// �r���[�v���W�F�N�V����
	ViewProjection* viewProjection_ = nullptr;
};
