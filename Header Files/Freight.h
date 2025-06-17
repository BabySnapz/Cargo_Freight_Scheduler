#pragma once
#include "Records.h"

class Freight : public Records
{
public:
    Freight(const std::string& id_, const std::string& location_, const std::string& time_)
        : Records(id_, location_, time_)
    {
    }
};
