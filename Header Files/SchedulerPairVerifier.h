#pragma once

#include "Cargo.h"
#include "Freight.h"

class SchedulerPairVerifier
{
public:
	static bool isMatched(const Cargo& cargo, const Freight& freight);
};

