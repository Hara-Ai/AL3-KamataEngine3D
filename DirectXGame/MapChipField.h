﻿#pragma once
#include <string>
#include <Vector3.h>
#include <vector>
#include "WorldTransform.h"


/// <sumary>
/// マップチップフィールド
/// <sumary>

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct  MapChipData 
{
	std::vector<std::vector<MapChipType>> deta;

};

struct IndexSet {
	uint32_t xIndex;
	uint32_t yIndex;
};

// 範囲短形
struct Rect 
{
	float left;   // 左端
	float right;  // 右端
	float bottom; // 下端
	float top;    // 上橋
};


class MapChipField 
{
public:

	void ResetMapChipData();
	uint32_t GetNumBlockVirtical() const;

	uint32_t GetNumBlockHorizontal() const;


	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	IndexSet GetMapChipIndexSetByPoition(const Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);


private:
	//1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;

	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;
	WorldTransform worldTransformBlocks_;
};

