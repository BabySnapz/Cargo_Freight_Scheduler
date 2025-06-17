#pragma once
#include "RecordsManager.h"
#include "Cargo.h"

class CargoManager : public RecordsManager
{
public:
    void addCargo(Cargo* cargo);

};
