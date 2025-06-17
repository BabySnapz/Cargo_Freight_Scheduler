#pragma once
#include "Records.h"

class Cargo : public Records
{
public:
    Cargo(const std::string& id_, const std::string& location_, const std::string& time_)
        : Records(id_, location_, time_)
    {
    }
};

