#pragma once
#include "iRecord.h"
#include "FreightType.h"

class iFreight : public iRecord 
{
public:
	virtual ~iFreight() = default;
	virtual FreightType getFreightType() const = 0;
	virtual int getMaxCapacity() const = 0;
	virtual int getRemainingCapacity() const = 0;
	virtual bool useCapacity(int amount) = 0;
};