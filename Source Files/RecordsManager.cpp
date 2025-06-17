#include "RecordsManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

RecordsManager::~RecordsManager()
{
    for (auto record : records)
        delete record;
}

void RecordsManager::addRecord(Records* record)
{
    records.push_back(record);
}

void RecordsManager::deleteRecord(const string& id)
{
    auto it = remove_if(records.begin(), records.end(),
        [&](Records* rec) { return rec->getID() == id; });

    if (it != records.end())
    {
        delete* it;
        records.erase(it, records.end());
    }
}

void RecordsManager::editRecord(const string& id, Records* updatedRecord)
{
    for (auto& rec : records)
    {
        if (rec->getID() == id)
        {
            delete rec;
            rec = updatedRecord;
            return;
        }
    }
}

void RecordsManager::loadFromFile(const string& filename)
{
    // Placeholder: implement file loading here
    cout << "Loading records from " << filename << endl;
}

vector<Records*> RecordsManager::getAllRecords() const
{
    return records;
}
