#pragma once
#include <cstdint>

/// <sumary>
/// �}�b�v�`�b�v�t�B�[���h
/// <sumary>

class MapChipField 
{
	//1�u���b�N�̃T�C�Y
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//�u���b�N�̌�
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 20;

	enum class MapChipType {
		kBlank,//��
		kBlock,//�u���b�N
	};
};