#pragma once
#include <cstdint>

/// <sumary>
/// マップチップフィールド
/// <sumary>

class MapChipField 
{
	//1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 20;

	enum class MapChipType {
		kBlank,//空白
		kBlock,//ブロック
	};
};