#pragma once
#include <string>
#include "iRecord.h"
#include "FreightType.h"


class Freight : public iRecord
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
    void showDetails() const override;
    void edit(const iRecord& editedRecord) override;

    const std::string& getLocation() const;
    const std::string& getTime() const;
    FreightType getFreightType() const;
    static int computeCapacity(FreightType t);
    int getMaxCapacity() const;
    int getRemainingCapacity() const;
    bool useCapacity(int amount);
};