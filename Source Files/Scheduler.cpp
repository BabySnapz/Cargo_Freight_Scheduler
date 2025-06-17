#include "Scheduler.h"
#include <iostream>

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

void Scheduler::runScheduling()
{
    vector<Records*> freights = freightMgr.getAllRecords();
    vector<Records*> cargos = cargoMgr.getAllRecords();
    

    cout << "\n--- Freight Records ---\n";
    for (Records* fRec : freights) {
        if (!fRec) {
            cerr << "Warning: Null freight record pointer skipped.\n";
            continue;
        }
        cout << fRec->getID() << " | " << fRec->getLocation() << " | " << fRec->getTime() << endl;
    }

    cout << "\n--- Cargo Records ---\n";
    for (Records* cRec : cargos) {
        if (!cRec) {
            cerr << "Warning: Null cargo record pointer skipped.\n";
            continue;
        }
        cout << cRec->getID() << " | " << cRec->getLocation() << " | " << cRec->getTime() << endl;
    }

    cout << "\nRunning scheduling algorithm...\n";

    for (Records* fRec : freights) {
        if (!fRec) continue;

        for (Records* cRec : cargos) {
            if (!cRec) continue;

            if (fRec->getLocation() == cRec->getLocation() &&
                cRec->getTime() < fRec->getTime()) {
                cout << "Match found: Freight " << fRec->getID()
                    << " paired with Cargo " << cRec->getID() << endl;
                matchedList.emplace_back(fRec, cRec);
                break; // one cargo per freight
            }
        }
    }

    cout << "\nMatching complete. " << matchedList.size() << " pair(s) found.\n";
    for (const auto& pair : matchedList) {
        cout << " Matched Freight " << pair.first->getID()
            << " with Cargo " << pair.second->getID() << endl;
    }

    for (Records* fRec : freights) {
        bool found = false;
        for (const auto& pair : matchedList) {
            if (pair.first == fRec) {
                found = true;
                break;
            }
        }
        if (!found) {
            unmatchedFreights.push_back(fRec);
        }
    }

    for (Records* cRec : cargos) {
        bool found = false;
        for (const auto& pair : matchedList) {
            if (pair.second == cRec) {
                found = true;
                break;
            }
        }
        if (!found) {
            unmatchedCargos.push_back(cRec);
        }
    }

    // Now print unmatched freights:
    cout << "\n--- Unmatched Freight Records ---\n";
    for (Records* fRec : unmatchedFreights) {
        cout << fRec->getID() << " | " << fRec->getLocation() << " | " << fRec->getTime() << endl;
    }

    // Print unmatched cargos:
    cout << "\n--- Unmatched Cargo Records ---\n";
    for (Records* cRec : unmatchedCargos) {
        cout << cRec->getID() << " | " << cRec->getLocation() << " | " << cRec->getTime() << endl;
    }

    cout << "Scheduling completed.\n";
}


void Scheduler::exportSchedule(const string& filepath)
{

    cout << "Exporting schedule to " << filepath << endl;
}

void Scheduler::addFreight(const Freight& freight)
{
    freightMgr.addFreight(new Freight(freight));
}

void Scheduler::editFreight(const string& id, const Freight& updatedFreight)
{
    freightMgr.editRecord(id, new Freight(updatedFreight));
}

void Scheduler::deleteFreight(const string& id)
{
    freightMgr.deleteRecord(id);
}

void Scheduler::addCargo(const Cargo& cargo)
{
    cargoMgr.addCargo(new Cargo(cargo));
}

void Scheduler::editCargo(const string& id, const Cargo& updatedCargo)
{
    cargoMgr.editRecord(id, new Cargo(updatedCargo));
}

void Scheduler::deleteCargo(const string& id)
{
    cargoMgr.deleteRecord(id);
}

std::vector<std::pair<Records*, Records*>> Scheduler::getMatchedList() const {
    return matchedList;
}

std::vector<Records*> Scheduler::getUnmatchedFreights() const {
    return unmatchedFreights;
}

std::vector<Records*> Scheduler::getUnmatchedCargos() const {
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