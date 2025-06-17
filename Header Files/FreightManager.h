#pragma once
#include "RecordsManager.h"
#include "Freight.h"

class FreightManager : public RecordsManager
{
public:
    void addFreight(Freight* freight);

};
