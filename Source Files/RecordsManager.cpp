#include "RecordsManager.h"  
#include <algorithm>  
#include <iostream>  
#include <fstream>  
#include <sstream>

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

#include <sstream> // Add this include for istringstream

void RecordsManager::loadFromFile(const string& filename)  
{  
    string cleanFilename = filename;

    if (!cleanFilename.empty() && cleanFilename.front() == '"' && cleanFilename.back() == '"') {
        cleanFilename = cleanFilename.substr(1, cleanFilename.length() - 2);
    }

    cout << "Loading records from: " << cleanFilename << endl;

    ifstream aFile(cleanFilename);
    if (!aFile.is_open()) {
        cerr << "Failed to open file: " << cleanFilename << endl;
        return;
    }

    string record_line;
    while (getline(aFile, record_line)) {
        string recId, recLocation, recTime;
        istringstream iss(record_line);

        if (!getline(iss, recId, ' ') ||
            !getline(iss, recLocation, ' ') ||
            !getline(iss, recTime, ' ')) {
            cerr << "Malformed line skipped: " << record_line << endl;
            continue;
        }

        Records* rec = new Records(recId, recLocation, recTime);
        addRecord(rec);
    }

    aFile.close();
    cout << "Data loaded successfully." << endl;
}

vector<Records*> RecordsManager::getAllRecords() const  
{  
    return records;  
}
