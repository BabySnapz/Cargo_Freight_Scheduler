#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

#include "Records.h"
#include "RecordsManager.h"

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
    fstream aFile;

    cout << "Loading records from " << filename << endl;

    aFile.open(filename, ios::in);
    if (aFile.is_open()) {
        string record_line;
        while (getline(aFile, record_line)) {
            string recId, recLocation, recTime;
            istringstream iss(record_line);

            getline(iss, recId, ',');
            getline(iss, recLocation, ',');
            getline(iss, recTime, ',');
            
            Records* rec = new Records(recId, recLocation, recTime);
            addRecord(rec);
        }
        aFile.close();
    }

}

vector<Records*> RecordsManager::getAllRecords() const
{
    return records;
}
