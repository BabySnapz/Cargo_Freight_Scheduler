#include <algorithm>  
#include <iostream>  
#include <fstream>  
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

#include "RecordsManager.h" 

RecordsManager::~RecordsManager()  
{  
    for (auto record : records)  
        delete record;  
}  

bool RecordsManager::addRecord(Records* record)
{
    auto exists = any_of(records.begin(), records.end()), [&](Records* r) {
            
        }
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

void RecordsManager::loadFromFile(const string& filename_in)
{
    string filename = filename_in; // make a local copy

    if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
        filename = filename.substr(1, filename.length() - 2);
    }

    cout << "Loading records from: " << filename << endl;

    ifstream aFile(filename);
    if (!aFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string record_line;
    while (getline(aFile, record_line)) {
        string recId, recLocation, recTime;
        istringstream iss(record_line);

        if (!getline(iss, recId, ',') ||
            !getline(iss, recLocation, ',') ||
            !getline(iss, recTime, ',')) {
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
