#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Records.h"

class RecordsManager
{
private:
    std::vector<Records*> records;

public:
    virtual ~RecordsManager();
    void addRecord(Records* record);
    void deleteRecord(const std::string& id);
    void editRecord(const std::string& id, Records* updatedRecord);
    void loadFromFile(const std::string& filename);
    std::vector<Records*> getAllRecords() const;
};

