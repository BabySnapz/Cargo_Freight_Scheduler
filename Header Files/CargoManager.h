#pragma once
#include <string>
#include <vector>

#include "Cargo.h"
#include "RecordsManager.h"

class CargoManager : public RecordsManager
{
private:
    std::vector<Cargo*> cargos;

public:
    Records* makeRecord(const std::string& id, const std::string& refuelStop, const std::string& refuelTime) override;
    bool addRecordToVector(Records* record) override;
    bool addCargo(Cargo* cargo);
    const std::vector<Cargo*>& getAllCargos() const;
};
