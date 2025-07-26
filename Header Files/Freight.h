#pragma once
#include <string>
#include <iostream>
#include "iFreight.h"
#include "FreightType.h"


class Freight : public iFreight
{
private:
    std::string id, location, time;
    FreightType freightType;
    int maxCapacity, remainingCapacity;

public:
    Freight(const std::string& id_, const std::string& location_,
        const std::string& time_, FreightType freightType_);
    ~Freight() override = default;
    const std::string& getID() const override;
    void edit(const iRecord& editedRecord) override;

    const std::string& getLocation() const override;
    const std::string& getTime() const override;
    FreightType getFreightType() const override;
    int getMaxCapacity() const override;
    int getRemainingCapacity() const override;
    bool useCapacity(int amount) override;

    std::unique_ptr<iRecord> clone() const override;

};
