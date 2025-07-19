#pragma once

#include <string>
#include <vector>
#include <utility>
#include "Freight.h"
#include "Cargo.h"

class iSchedulerManager
{
public:
    virtual void setStrategy() = 0;
    virtual void exportSchedule(const std::string& filepath) = 0;
    virtual std::vector<std::pair<const Freight&, const Cargo&>> getMatchedList() = 0;
    virtual ~iSchedulerManager() = default;
};

