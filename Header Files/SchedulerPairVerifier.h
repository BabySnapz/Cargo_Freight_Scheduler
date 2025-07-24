#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath> // for std::abs

#include "Cargo.h"
#include "Freight.h"

class SchedulerPairVerifier
{
private:
	Cargo cargo;
	Freight freight;
public:
	static bool isMatched(const Cargo& cargo, const Freight& freight);

};

