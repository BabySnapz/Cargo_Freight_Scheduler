#pragma once
#include <string>
#include <vector>

#include "Freight.h"
#include "RecordsManager.h"

class FreightManager : public RecordsManager
{
public: 
	Records* makeRecord(const std::string& id, const std::string& destination, const std::string& arrivalTime) override;
    bool addFreight(Freight* freight);
};
