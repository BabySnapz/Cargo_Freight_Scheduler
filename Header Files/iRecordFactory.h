#pragma once
#include <memory>
#include <string>
#include <vector>
#include "iRecordParams.h"	
#include "iRecord.h"

class iRecordFactory
{
public:
	virtual ~iRecordFactory() = default;
	virtual std::unique_ptr<iRecordParams> makeParams() const = 0;
	virtual std::unique_ptr<iRecord> create(const iRecordParams& params) const = 0;
};