#pragma once
#include "RecordsManager.h"
#include "Freight.h"
#include <string>
#include <vector>


class FreightManager : public RecordsManager
{
public:
    void addFreight(Freight* freight);
	void loadFromFile(const std::string& filename);

};
