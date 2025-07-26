#pragma once
#include <string>
#include <memory>

class iRecord
{
public:
    virtual ~iRecord() = default;
    virtual void edit(const iRecord& editedRecord) = 0;
    virtual const std::string& getID() const = 0;
    virtual const std::string& getLocation() const = 0;
    virtual const std::string& getTime() const = 0;
    virtual std::unique_ptr<iRecord> clone() const = 0;
};
