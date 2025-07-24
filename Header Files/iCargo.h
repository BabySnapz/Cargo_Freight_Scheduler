#pragma once
#include "iRecord.h"

class iCargo : public iRecord 
{
public:
	virtual ~iCargo() = default;
	virtual int getCargoGrouping() const = 0;
};