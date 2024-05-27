#include "MapChipField.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <map>

namespace
{
	std::map<std::string, MapChipType> mapChipTable = 
	{
		{"0", MapChipType::kBlank},
		{"0", MapChipType::kBlock},
	};

}

void MapChipField::ResetMapChipData() 
{
	mapChipData_.deta.clear(); 
	mapChipData_.deta.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.deta)
	{
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

uint32_t MapChipField::GetNumBlockVirtical() const { return kNumBlockVirtical; }
uint32_t MapChipField::GetNumBlockHorizontal() const { return kNumBlockHorizontal; }

void MapChipField::LoadMapChipCsv(const std::string& filePath) 
{
	ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;

	mapChipCsv << file.rdbuf();

	file.close();

	//for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	//{
	//	getline(mapChipCsv, line);
	//
	//	std::istringstream line_stream(line);
	//
	//	for (uint32_t j = 0; j < kNumBlockHorizontal; ++j)
	//	{
	//		std::string word;
	//		getline(line_stream, word, ",");
	//
	//		if (mapChipTable.contains(word))
	//		{
	//			mapChipData_.deta[i][j] = mapChipTable[word];
	//		}
	//	}
	//}
}

