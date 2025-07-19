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
    CargoParams() = default;
    ~CargoParams() override = default;
    void fieldsFromFile(std::vector<std::string>& tokens) override;

    CargoParams& setID(const std::string& id_);
    CargoParams& setLocation(const std::string& location_);
    CargoParams& setTime(const std::string& time_);
    CargoParams& setCargoGrouping(int cargoGrouping_);

    std::string& getID() const;
    std::string& getLocation() const;
    std::string& getTime() const;
    int getCargoGrouping() const;
};

