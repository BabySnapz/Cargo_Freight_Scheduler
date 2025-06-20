#pragma once
#include <string>
#include <vector>

#include "Cargo.h"
#include "RecordsManager.h"

class CargoManager : public RecordsManager
{
public:
    Records* makeRecord(const std::string& id, const std::string& refuelStop, const std::string& refuelTime) override;
    bool addCargo(Cargo* cargo);
};
