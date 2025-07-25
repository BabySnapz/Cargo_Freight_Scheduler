#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>

#include "iCargo.h"
#include "iFreight.h"

class SchedulerPairVerifier
{
public:
    static bool isMatched(const iCargo& cargo, const iFreight& freight);
};

