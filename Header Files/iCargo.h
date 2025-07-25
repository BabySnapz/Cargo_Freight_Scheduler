#pragma once
#include "iRecord.h"
#include <iostream>

class iCargo : public iRecord 
{
public:
	virtual ~iCargo() = default;
	virtual int getCargoGrouping() const = 0;
	virtual bool useCargoGrouping(int amount) = 0;

	friend std::ostream& operator<<(std::ostream& out, const iCargo& aCargo);
};