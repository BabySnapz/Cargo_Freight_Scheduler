#pragma once
#include <string>
#include <vector>
#include "iRecordParams.h"

class CargoParams :
    public iRecordParams
{
private:
    std::string id;
    std::string location;
    std::string time;
    int cargoGrouping;
public:
    CargoParams() : cargoGrouping(0) {}
    ~CargoParams() override = default;
    void fieldsFromFile(const std::vector<std::string>& tokens) override;

    CargoParams& setID(const std::string& id_);
    CargoParams& setLocation(const std::string& location_);
    CargoParams& setTime(const std::string& time_);
    CargoParams& setCargoGrouping(int cargoGrouping_);

    const std::string& getID() const;
    const std::string& getLocation() const;
    const std::string& getTime() const;
    int getCargoGrouping() const;
};