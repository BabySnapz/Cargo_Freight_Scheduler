#pragma once
#include "RecordsManager.h"
#include "Cargo.h"

class CargoManager : public RecordsManager
{
public:
    bool addCargo(Cargo* cargo);
    void loadFromFile(const std::string& filename); //void loadCargo
};
