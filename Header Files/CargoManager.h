#pragma once
#include "RecordsManager.h"
#include "Cargo.h"

class CargoManager : public RecordsManager
{
public:
    void addCargo(Cargo* cargo);
    void loadFromFile(const std::string& filename);
};
