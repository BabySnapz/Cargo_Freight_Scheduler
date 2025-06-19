#include "Scheduler.h"

#include <iostream>
#include <fstream>

using namespace std;

void Scheduler::Start()
{
    cout << "Scheduler started." << endl;
}

void Scheduler::loadFreights(const string& filepath)
{
    freightMgr.loadFromFile(filepath);
}

void Scheduler::loadCargos(const string& filepath)
{
    cargoMgr.loadFromFile(filepath);
}

// Helper function to remove matches involving a specific freight ID
void Scheduler::removeMatchesWithFreightID(const std::string& freightID)
{
    auto it = matchedList.begin();
    while (it != matchedList.end()) {
        if (it->first->getID() == freightID) {
            cout << "Removing match: Freight " << it->first->getID()
                << " with Cargo " << it->second->getID()
                << " (freight was edited)" << endl;
            it = matchedList.erase(it);
        }
        else {
            ++it;
        }
    }
}

// Helper function to remove matches involving a specific cargo ID
void Scheduler::removeMatchesWithCargoID(const std::string& cargoID)
{
    auto it = matchedList.begin();
    while (it != matchedList.end()) {
        if (it->second->getID() == cargoID) {
            cout << "Removing match: Freight " << it->first->getID()
                << " with Cargo " << it->second->getID()
                << " (cargo was edited)" << endl;
            it = matchedList.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Scheduler::runScheduling()
{
    auto trim = [](const std::string& str) -> std::string {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";

        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, (last - first + 1));
        };

    vector<Records*> freights = freightMgr.getAllRecords();
    vector<Records*> cargos = cargoMgr.getAllRecords();
    
    cout << "\nRunning scheduling algorithm...\n";

    for (Records* fRec : freights) {
        if (!fRec) continue;

        for (Records* cRec : cargos) {
            if (!cRec) continue;

            if (fRec->getLocation() == cRec->getLocation() &&
                cRec->getTime() < fRec->getTime()) {

                Freight* freight = dynamic_cast<Freight*>(fRec);
                Cargo* cargo = dynamic_cast<Cargo*>(cRec);

                if (!freight || !cargo) continue;

                bool alreadyMatched = false;
                for (const auto& pair : matchedList) {
                    if (pair.first == freight && pair.second == cargo) {
                        alreadyMatched = true;
                        break;
                    }
                }

                if (!alreadyMatched) {
                    matchedList.emplace_back(freight, cargo);
                    cout << "Match found: Freight " << freight->getID()
                        << " paired with Cargo " << cargo->getID() << endl;
                }

                break;
            }
        }
    }

    cout << "\nMatching complete. " << matchedList.size() << " pair(s) found.\n";
    for (const auto& pair : matchedList) {
        cout << " Matched Freight " << pair.first->getID()
            << " with Cargo " << pair.second->getID() << endl;
    }

    cout << "\n--- Matched Freight and Cargo Records ---\n";
    cout << left
        << setw(8) << "F_ID" << setw(12) << "F_Location" << setw(8) << "F_Time" << " | "
        << setw(8) << "C_ID" << setw(12) << "C_Location" << setw(8) << "C_Time" << endl;
    cout << string(65, '-') << endl;

    for (const auto& pair : matchedList) {
        Freight* f = pair.first;
        Cargo* c = pair.second;

        cout << left
            << setw(8) << f->getID()
            << setw(12) << f->getLocation()
            << setw(8) << f->getTime() << " | "
            << setw(8) << c->getID()
            << setw(12) << c->getLocation()
            << setw(8) << c->getTime() << endl;
    }

    // Rebuild unmatchedFreights and unmatchedCargos based on new matches
    unmatchedFreights.clear();
    unmatchedCargos.clear();

    for (Records* fRec : freights) {
        Freight* freight = dynamic_cast<Freight*>(fRec);
        if (!freight) continue;

        bool matched = false;
        for (const auto& pair : matchedList) {
            if (pair.first == freight) {
                matched = true;
                break;
            }
        }
        if (!matched) unmatchedFreights.push_back(freight);
    }

    for (Records* cRec : cargos) {
        Cargo* cargo = dynamic_cast<Cargo*>(cRec);
        if (!cargo) continue;

        bool matched = false;
        for (const auto& pair : matchedList) {
            if (pair.second == cargo) {
                matched = true;
                break;
            }
        }
        if (!matched) unmatchedCargos.push_back(cargo);
    }

    cout << "\n--- Unmatched Freight Records ---\n";
    cout << left
        << setw(8) << "F_ID"
        << setw(12) << "F_Location"
        << setw(8) << "F_Time"
        << endl;
    cout << string(30, '-') << endl;

    for (Freight* f : unmatchedFreights) {
        cout << left
            << setw(8) << f->getID()
            << setw(12) << f->getLocation()
            << setw(8) << f->getTime()
            << endl;
    }

    cout << "\n--- Unmatched Cargo Records ---\n";
    cout << left
        << setw(8) << "C_ID"
        << setw(12) << "C_Location"
        << setw(8) << "C_Time"
        << endl;
    cout << string(30, '-') << endl;

    for (Cargo* c : unmatchedCargos) {
        cout << left
            << setw(8) << c->getID()
            << setw(12) << c->getLocation()
            << setw(8) << c->getTime()
            << endl;
    }

    cout << "Scheduling completed.\n";
}



void Scheduler::exportSchedule(const string& filepath)
{
    fs::path inputPath(filepath);

    fs::path filePath;

    // If the user included a filename (e.g., ends with .txt), use it directly
    if (inputPath.has_filename() && inputPath.extension() == ".txt") {
        filePath = inputPath;
    }
    else {
        // Otherwise, treat it as a folder and append Schedule.txt
        if (!fs::exists(inputPath)) {
            try {
                fs::create_directories(inputPath);
            }
            catch (const fs::filesystem_error& e) {
                cerr << "Failed to create directory: " << e.what() << endl;
                return;
            }
        }
        filePath = inputPath / "Schedule.txt";
    }

    ofstream outFile(filePath);

    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << filepath << endl;
        return;
    }

    outFile << "--- Matched Freight and Cargo Records ---\n";
    outFile << left
        << setw(8) << "F_ID"
        << setw(12) << "F_Location"
        << setw(8) << "F_Time"
        << " | "
        << setw(8) << "C_ID"
        << setw(12) << "C_Location"
        << setw(8) << "C_Time"
        << "\n";
    outFile << string(65, '-') << "\n";

    for (const auto& pair : matchedList) {
        Freight* f = pair.first;
        Cargo* c = pair.second;

        outFile << left
            << setw(8) << f->getID()
            << setw(12) << f->getLocation()
            << setw(8) << f->getTime()
            << " | "
            << setw(8) << c->getID()
            << setw(12) << c->getLocation()
            << setw(8) << c->getTime()
            << "\n";
    }

    outFile << "\n--- Unmatched Freight Records ---\n";
    outFile << left
        << setw(8) << "F_ID"
        << setw(12) << "F_Location"
        << setw(8) << "F_Time"
        << "\n";
    outFile << string(30, '-') << "\n";

    for (Freight* f : unmatchedFreights) {
        outFile << left
            << setw(8) << f->getID()
            << setw(12) << f->getLocation()
            << setw(8) << f->getTime()
            << "\n";
    }

    outFile << "\n--- Unmatched Cargo Records ---\n";
    outFile << left
        << setw(8) << "C_ID"
        << setw(12) << "C_Location"
        << setw(8) << "C_Time"
        << "\n";
    outFile << string(30, '-') << "\n";

    for (Cargo* c : unmatchedCargos) {
        outFile << left
            << setw(8) << c->getID()
            << setw(12) << c->getLocation()
            << setw(8) << c->getTime()
            << "\n";
    }

    outFile << "Scheduling completed.\n";
    outFile.close();
    cout << "Exporting schedule to " << filepath << endl;
}

bool Scheduler::addFreight(const Freight& freight)
{
   return freightMgr.addFreight(new Freight(freight));
}

bool Scheduler::editFreight(const string& id, const Freight& updatedFreight)
{
   return freightMgr.editRecord(id, new Freight(updatedFreight));
}

bool Scheduler::deleteFreight(const string& id)
{
   return freightMgr.deleteRecord(id);
}

bool Scheduler::addCargo(const Cargo& cargo)
{
    return cargoMgr.addCargo(new Cargo(cargo));
}

bool Scheduler::editCargo(const string& id, const Cargo& updatedCargo)
{
    return cargoMgr.editRecord(id, new Cargo(updatedCargo));
}

bool Scheduler::deleteCargo(const string& id)
{
    return cargoMgr.deleteRecord(id);
}

std::vector<std::pair<Freight*, Cargo*>> Scheduler::getMatchedList() const {
    return matchedList;
}

std::vector<Freight*> Scheduler::getUnmatchedFreights() const {
    return unmatchedFreights;
}

std::vector<Cargo*> Scheduler::getUnmatchedCargos() const {
    return unmatchedCargos;
}

FreightManager& Scheduler::getFreightManager()
{
    return freightMgr;
}

CargoManager& Scheduler::getCargoManager()
{
    return cargoMgr;
}