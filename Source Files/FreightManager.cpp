#include "FreightManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool FreightManager::addFreight(Freight* freight)
{
  return addRecord(freight);
}

void FreightManager::loadFromFile(const string& filename_in)
{
    string filename = filename_in;
    if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
        filename = filename.substr(1, filename.length() - 2);
    }

    cout << "Loading freight records from: " << filename << endl;

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

        Freight* freight = new Freight(recId, recLocation, recTime);
        addFreight(freight);  // uses existing function
    }

    aFile.close();
    cout << "Freight data loaded successfully." << endl;
}

