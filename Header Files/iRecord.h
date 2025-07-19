#pragma once
#include <string>

class iRecord
{
    //friend std::ostream& operator<<(std::ostream& out, const Records& aRecord);
public:
    virtual ~iRecord() = default;
    virtual std::string& getID() const = 0;
    virtual void showDetails() const = 0;
    virtual void edit(const iRecord& editedRecord) = 0;
};
