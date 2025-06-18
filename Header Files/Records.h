#pragma once

#include <string>
#include <iostream>

class Records
{
    friend std::ostream& operator<<(std::ostream& out, const Records& aRecord);

private:
    std::string id;
    std::string location;
    std::string time;

public:
    Records(const std::string& id, const std::string& location, const std::string& time);

    const std::string& getID() const;
    void setID(const std::string& id);

    const std::string& getLocation() const;
    void setLocation(const std::string& location);

    const std::string& getTime() const;
    void setTime(const std::string& time);

    void showDetails() const;
};
