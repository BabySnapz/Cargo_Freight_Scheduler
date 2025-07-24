#pragma once
#include <string>
#include <vector>
#include "iRecordParams.h"
#include "FreightType.h"

class FreightParams : public iRecordParams
{
private:
    std::string id;
    std::string location;
    std::string time;
    FreightType freightType{ FreightType::MiniMover };

public:
    FreightParams() = default;
    ~FreightParams() override = default;
    void fieldsFromFile(std::vector<std::string>& tokens) override;

    FreightParams& setID(const std::string& id_);
    FreightParams& setLocation(const std::string& location_);
    FreightParams& setTime(const std::string& time_);
    FreightParams& setFreightType(const FreightType& freightType_);

    const std::string& getID() const;
    const std::string& getLocation() const;
    const std::string& getTime() const;
    FreightType getFreightType() const;
};