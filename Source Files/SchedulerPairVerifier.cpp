#include "SchedulerPairVerifier.h"

bool SchedulerPairVerifier::isMatched(const Cargo& cargo, const Freight& freight) 
{
    return cargo.getLocation() == freight.getLocation() && cargo.getTime() <= freight.getTime();
}