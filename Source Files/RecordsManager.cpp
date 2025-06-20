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

bool RecordsManager::addRecordToVector(Records* record) {
    bool existsFlag = false;

    for (Records* r : records) {
        if (r->getID() == record->getID()) {
            existsFlag = true;
            break;
        }
    }
    if (existsFlag) {
        delete record;
        return false;
    }

    records.push_back(record);
    return true;
}

bool RecordsManager::deleteRecord(const string& id)  
{  
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it)->getID() == id) {
            delete *it;
            records.erase(it);
            return true;
        }
    } 
    return false;
}  

bool RecordsManager::editRecord(const string& id, Records* updatedRecord)  
{  
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it)->getID() == id) {
            delete* it;
            *it = updatedRecord;
            return true;
        }
    }
    delete updatedRecord;
    return false;
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
            //cerr << "Malformed line skipped: " << record_line << endl; For debugging
            continue;
        }

        Records* rec = makeRecord(recId, recLocation, recTime);
        addRecordToVector(rec);
    }
    aFile.close();
    cout << "Data loaded successfully." << endl;
}

const vector<Records*>& RecordsManager::getAllRecords() const  
{  
    return records;  
}
