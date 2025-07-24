#pragma once
#include <string>

class iRecord
{
public:
    virtual ~iRecord() = default;
    virtual const std::string& getID() const = 0;
    virtual void edit(const iRecord& editedRecord) = 0;
};
