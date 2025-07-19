#pragma once
#include <string>
#include "iRecord.h"

class Cargo : public iRecord
{
private:
    std::string id, location, time;
    int cargoGrouping;

public:
    Cargo(const std::string& id_, const std::string& location_, const std::string& time_, int cargoGrouping_);
    ~Cargo() override = default;
    std::string& getID() const override;
    void showDetails() const override;
    void edit(const iRecord& editedRecord) override;

    std::string& getLocation() const;
    std::string& getTime() const;
    int getCargoGrouping() const;
};

