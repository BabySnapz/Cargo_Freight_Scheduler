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
    
	/*  THis part is used for debugging purposes, to print the records loaded
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
    }*/
    

    cout << "\nRunning scheduling algorithm...\n";

    for (Records* fRec : freights) {
        if (!fRec) continue;

        for (Records* cRec : cargos) {
            if (!cRec) continue;

            if (fRec->getLocation() == cRec->getLocation() &&
                cRec->getTime() < fRec->getTime()) {

                cout << "Match found: Freight " << fRec->getID()
                    << " paired with Cargo " << cRec->getID() << endl;

                Freight* freight = dynamic_cast<Freight*>(fRec);
                Cargo* cargo = dynamic_cast<Cargo*>(cRec);

                if (!freight) {
                    cout << "  [Debug] Failed to cast fRec to Freight*\n";
                }
                if (!cargo) {
                    cout << "  [Debug] Failed to cast cRec to Cargo*\n";
                }
                if (freight && cargo) {
                    matchedList.emplace_back(freight, cargo);
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


    for (Records* fRec : freights) {
        bool found = false;
        for (const auto& pair : matchedList) {
            if (pair.first == fRec) {
                found = true;
                break;
            }
        }
        if (!found) {
            Freight* freight = dynamic_cast<Freight*>(fRec);
            if (freight) {
                unmatchedFreights.push_back(freight);
            }

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
            Cargo* cargo = dynamic_cast<Cargo*>(cRec);
            if (cargo) {
                unmatchedCargos.push_back(cargo);
            }

        }
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