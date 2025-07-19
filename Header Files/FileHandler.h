#pragma once
#include <string>
#include <vector>
#include <memory>
#include "iRecordFactory.h"
#include "iRecord.h"

class FileHandler
{
public:
	FileHandler() = default;
	~FileHandler() = default;
	std::vector<std::unique_ptr<iRecord>> load(
		const std::string& filePath,
		const iRecordFactory& factory) const;
};

