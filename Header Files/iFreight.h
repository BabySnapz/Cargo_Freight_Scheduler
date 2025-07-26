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

	std::unique_ptr<iRecord> clone() const override = 0;

	friend std::ostream& operator<<(std::ostream& out, const iFreight& aFreight);
};