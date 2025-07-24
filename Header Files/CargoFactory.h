#pragma once
#include "iRecordFactory.h"
#include "CargoParams.h"

class CargoFactory :
    public iRecordFactory
{
public:
    ~CargoFactory() override = default;
    std::unique_ptr<iRecordParams> makeEmptyParams() const override;
    std::unique_ptr<iRecord> create(const iRecordParams& params) const override;
};

