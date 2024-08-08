#include "MapchipField.h"
#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>

namespace {

std::map<std::string, MapChipType> mapchipTabale = {

    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};
}

void MapchipField::ResetMapChipData() {

	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {

		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapchipField::LoadMapChipCsv(const std::string& filePath) {

	// マップチップデータをリセット
	ResetMapChipData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップcsv
	std::stringstream mapChipCsv;
	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	// ファイルを閉じる
	file.close();

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

		std::string line;
		getline(mapChipCsv, line);

		// 1行分の文字列をストリーミングに変換して解析しやすくする
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {

			std::string word;
			getline(line_stream, word, ',');

			if (mapchipTabale.contains(word)) {

				mapChipData_.data[i][j] = mapchipTabale[word];
			}
		}
	}
}

MapChipType MapchipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {

	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}

	if (yIndex < 0 || kNumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapchipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockHorizontal - 1 - yIndex), 0); }