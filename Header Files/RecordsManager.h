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
    virtual Records* makeRecord(const std::string& id, const std::string& location, const std::string& time) = 0;
    virtual bool addRecordToVector(Records* record) = 0;
    bool deleteRecord(const std::string& id);
    bool editRecord(const std::string& id, Records* updatedRecord);
    void loadFromFile(const std::string& filename);
    const std::vector<Records*>& getAllRecords() const;
};

