#include "CargoManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void CargoManager::addCargo(Cargo* cargo)
{
    addRecord(cargo);
}

void CargoManager::loadFromFile(const string& filename_in)
{
    string filename = filename_in;
    if (!filename.empty() && filename.front() == '"' && filename.back() == '"') {
        filename = filename.substr(1, filename.length() - 2);
    }

    cout << "Loading cargo records from: " << filename << endl;

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

        Cargo* cargo = new Cargo(recId, recLocation, recTime);
        addCargo(cargo);
    }

    aFile.close();
    cout << "Cargo data loaded successfully." << endl;
}
