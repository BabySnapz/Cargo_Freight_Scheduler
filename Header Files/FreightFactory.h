#pragma once
#include "iRecordFactory.h"
#include "FreightParams.h"

class FreightFactory :
    public iRecordFactory
{
public:
    ~FreightFactory() override = default;
    std::unique_ptr<iRecordParams> makeEmptyParams() const override;
    std::unique_ptr<iRecord> create(const iRecordParams& params) const override;
};

