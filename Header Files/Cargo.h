#pragma once
#include <string>
#include <iostream>
#include "iCargo.h"

class Cargo : public iCargo
{
private:
    std::string id, location, time;
    int cargoGrouping;

public:
    Cargo(const std::string& id_, const std::string& location_, 
        const std::string& time_, int cargoGrouping_);
    ~Cargo() override = default;
    const std::string& getID() const override;
    void edit(const iRecord& editedRecord) override;

    const std::string& getLocation() const override;
    const std::string& getTime() const override;
    int getCargoGrouping() const override;
    bool useCargoGrouping(int amount) override;

    std::unique_ptr<iRecord> clone() const override;
};

