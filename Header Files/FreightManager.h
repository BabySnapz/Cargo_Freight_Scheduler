#pragma once
#include <string>
#include <vector>

#include "Freight.h"
#include "RecordsManager.h"

class FreightManager : public RecordsManager
{
private:
	std::vector<Freight*> freights;

public: 
	Records* makeRecord(const std::string& id, const std::string& destination, const std::string& arrivalTime) override;
	bool addRecordToVector(Records* record) override;
    bool addFreight(Freight* freight);
	const std::vector<Freight*>& getAllFreights() const;
};
