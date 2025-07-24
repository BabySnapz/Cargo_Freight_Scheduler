#pragma once
#include <string>
#include <vector>

class iRecordParams
{
public:
	virtual ~iRecordParams() = default;
	virtual void fieldsFromFile(const std::vector<std::string>& tokens) = 0;
};
