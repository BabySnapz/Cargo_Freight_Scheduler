#include <iostream>
#include <thread>   
#include <chrono>
#include <limits>

#include "TUI.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "SchedulerManager.h"
#include "FileHandler.h"

using namespace std;

namespace 
{
    void clearScreen() 
    {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
    }

    void pauseForEnter() 
    {
        cout << "\nPress Enter to continue...";
        cin.get();
    }

    void clearInputBuffer() 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

TUI::TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s)
    : freightmgr(f), cargomgr(c), schedulermgr(s) {
}

void TUI::run() 
{
    clearScreen();
    welcome();
    while (true) 
    {
        displayMenu();
        int choice = getValidatedChoice();
        switch (choice) 
        {
        case 1: handleFreightMenu(); break;
        case 2: handleCargoMenu(); break;
        case 3: handleSchedulerMenu(); break;
        case 0: cout << "Exiting program.\n"; return;
        default:
            cout << "Invalid choice. Please try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}


void TUI::welcome() 
{
    clearScreen();
    cout << "======================================================\n";
    cout << "** Welcome to Freight & Cargo Scheduling System **\n";
    cout << "======================================================\n";
    pauseForEnter();
}

void TUI::displayMenu() {
    cout << "\n=== Main Menu ===\n"
        << "1. Freight Management\n"
        << "2. Cargo Management\n"
        << "3. Scheduler Management\n"
        << "0. Exit\n"
        << "========================\n"
        << "Enter your choice: ";
}

int TUI::getValidatedChoice() 
{
    int choice;
    while (!(cin >> choice)) 
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        clearInputBuffer();
    }
    clearInputBuffer();
    return choice;
}


/****************** Freight Menu **********************************/

// Freight Menu Handlers
void TUI::handleFreightMenu() {
    while (true) {
        clearScreen();
        cout << "\n--- Freight Menu ---\n"
            << "1. Load Freight from file\n"
            << "2. Create Freight\n"
            << "3. Add Freight\n"
            << "4. Edit Freight\n"
            << "5. Remove Freight\n"
            << "6. View All Freights\n"
            << "0. Back to Main Menu\n"
            << "========================\n"
            << "Enter your choice: ";
        int choice = getValidatedChoice();
        switch (choice) {
        case 1: loadFreight(); break;
        case 2: createFreight(); break;
        case 3: addFreight(); break;
        case 4: editFreight(); break;
        case 5: removeFreight(); break;
        case 6: viewAllFreights(); break;
        case 0: return;
        default:
            cout << "Invalid option. Try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void TUI::loadFreight() {
    cout << "\nEnter file path: ";
    string path;
    getline(cin, path);
    if (freightmgr->loadFromFile(path)) {
        cout << "File loaded successfully!\n";
    }
    else {
        cout << "Failed to load file. Check path/permissions.\n";
    }
    pauseForEnter();
}

void TUI::createFreight() {
    string id, location, time;
    int typeChoice;
    cout << "\nEnter Freight ID: ";
    getline(cin, id);
    cout << "Enter Location: ";
    getline(cin, location);
    cout << "Enter Time: ";
    getline(cin, time);
    cout << "Select Freight Type (1=MiniMover,2=CargoCruiser,3=MegaCarrier): ";
    typeChoice = getValidatedChoice();
    FreightType type = (typeChoice == 2 ? FreightType::CargoCruiser
        : typeChoice == 3 ? FreightType::MegaCarrier
        : FreightType::MiniMover);
    freightmgr->createFreight(id, location, time, type);
    cout << "Freight created successfully!\n";
    pauseForEnter();
}

void TUI::addFreight() {
    string id, location, time;
    int typeChoice;
    cout << "\nEnter Freight ID: "; getline(cin, id);
    cout << "Enter Location: "; getline(cin, location);
    cout << "Enter Time: "; getline(cin, time);
    cout << "Select Freight Type (1=MiniMover,2=CargoCruiser,3=MegaCarrier): ";
    typeChoice = getValidatedChoice();
    FreightType type = (typeChoice == 2 ? FreightType::CargoCruiser
        : typeChoice == 3 ? FreightType::MegaCarrier
        : FreightType::MiniMover);
    FreightParams params;
    params.setID(id).setLocation(location).setTime(time).setFreightType(type);
    auto freight = make_unique<Freight>(params.getID(), params.getLocation(), params.getTime(), params.getFreightType());
    freightmgr->addFreight(move(freight));
    cout << "Freight added successfully!\n";
    pauseForEnter();
}

void TUI::editFreight() {
    string id;
    cout << "\nEnter ID of freight to edit: "; getline(cin, id);
    cout << "Enter new Location: "; string loc; getline(cin, loc);
    cout << "Enter new Time: "; string tm; getline(cin, tm);
    cout << "Select Freight Type (1=MiniMover,2=CargoCruiser,3=MegaCarrier): ";
    int tc = getValidatedChoice();
    FreightType type = (tc == 2 ? FreightType::CargoCruiser
        : tc == 3 ? FreightType::MegaCarrier
        : FreightType::MiniMover);
    FreightParams params;
    params.setLocation(loc).setTime(tm).setFreightType(type);
    freightmgr->editFreight(id, params);
    cout << "Freight edited successfully!\n";
    pauseForEnter();
}

void TUI::removeFreight() {
    cout << "\nEnter ID of freight to remove: ";
    string id; getline(cin, id);
    freightmgr->removeFreight(id);
    cout << "Freight removed.\n";
    pauseForEnter();
}

void TUI::viewAllFreights() {
    auto list = freightmgr->getAllFreights();
    if (list.empty()) cout << "No freights available.\n";
    else {
        cout << "Total Freights: " << list.size() << "\n";
        for (auto f : list) cout << *f << "\n";
    }
    pauseForEnter();
}


/****************** Cargo Menu **********************************/
void TUI::handleCargoMenu() {
    while (true) {
        clearScreen();
        cout << "\n--- Cargo Menu ---\n"
            << "1. Load Cargo from file\n"
            << "2. Create Cargo\n"
            << "3. Add Cargo\n"
            << "4. Edit Cargo\n"
            << "5. Delete Cargo\n"
            << "6. View All Cargos\n"
            << "0. Back to Main Menu\n"
            << "========================\n"
            << "Enter your choice: ";
        int choice = getValidatedChoice();
        switch (choice) {
        case 1: loadCargo(); break;
        case 2: createCargo(); break;
        case 3: addCargo(); break;
        case 4: editCargo(); break;
        case 5: removeCargo(); break;
        case 6: viewAllCargos(); break;
        case 0: return;
        default:
            cout << "Invalid option. Try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void TUI::loadCargo() {
    cout << "\nEnter file path: ";
    string path;
    getline(cin, path);
    if (cargomgr->loadFromFile(path)) {
        cout << "File loaded successfully!\n";
    }
    else {
        cout << "Failed to load file.\n";
    }
    pauseForEnter();
}

void TUI::createCargo() {
    string id, location, time;
    int grouping;
    cout << "\nEnter Cargo ID: "; getline(cin, id);
    cout << "Enter Location: "; getline(cin, location);
    cout << "Enter Time: "; getline(cin, time);
    cout << "Enter Cargo Grouping: ";
    cin >> grouping;
    clearInputBuffer();
    cargomgr->createCargo(id, location, time, grouping);
    cout << "Cargo created successfully!\n";
    pauseForEnter();
}

void TUI::addCargo() {
    string id, location, time;
    int grouping;
    cout << "\nEnter Cargo ID: "; getline(cin, id);
    cout << "Enter Location: "; getline(cin, location);
    cout << "Enter Time: "; getline(cin, time);
    cout << "Enter Cargo Grouping: ";
    cin >> grouping;
    clearInputBuffer();
    auto cargo = make_unique<Cargo>(id, location, time, grouping);
    cargomgr->addCargo(move(cargo));
    cout << "Cargo added successfully!\n";
    pauseForEnter();
}

void TUI::editCargo() {
    string id, loc, tm;
    int grouping;
    cout << "\nEnter ID of cargo to edit: "; getline(cin, id);
    cout << "Enter new Location: "; getline(cin, loc);
    cout << "Enter new Time: "; getline(cin, tm);
    cout << "Enter new Grouping: ";
    cin >> grouping;
    clearInputBuffer();
    CargoParams params;
    params.setLocation(loc).setTime(tm).setCargoGrouping(grouping);
    cargomgr->editCargo(id, params);
    cout << "Cargo edited successfully!\n";
    pauseForEnter();
}

void TUI::removeCargo() {
    cout << "\nEnter ID of cargo to remove: ";
    string id;
    getline(cin, id);
    cargomgr->removeCargo(id);
    cout << "Cargo removed.\n";
    pauseForEnter();
}

void TUI::viewAllCargos() {
    auto list = cargomgr->getAllCargos();
    if (list.empty()) cout << "No cargos available.\n";
    else {
        cout << "Total Cargos: " << list.size() << "\n";
        for (auto c : list) cout << *c << "\n";
    }
    pauseForEnter();
}



/****************** Scheduler Menu *******************************/
void TUI::handleSchedulerMenu() {
    while (true) {
        clearScreen();
        cout << "\n=== Scheduler Management ===\n"
            << "1. Set Scheduling Strategy\n"
            << "2. Export Schedule to file\n"
            << "3. View Current Schedule\n"
            << "0. Back to Main Menu\n"
            << "========================\n"
            << "Enter your choice: ";
        int choice = getValidatedChoice();
        switch (choice) {
        case 1: setStrategy(); break;
        case 2: exportSchedule(); break;
        case 3: viewSchedule(); break;
        case 0: return;
        default:
            cout << "Invalid option. Try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void TUI::setStrategy() {
    cout << "\nSelect Scheduling Strategy:\n1. Sort by Time\n2. Sort by Capacity\nChoice: ";
    int option = getValidatedChoice();
    switch (option) {
    case 1: {
        auto strategy = make_unique<SortByTime>();
        schedulermgr->setStrategy(strategy.get());
        schedulermgr->createMatchedList(freightmgr->getAllFreights(), cargomgr->getAllCargos());
        break;
    }
    case 2: {
        auto strategy = make_unique<SortByCapacity>();
        schedulermgr->setStrategy(strategy.get());
        schedulermgr->createMatchedList(freightmgr->getAllFreights(), cargomgr->getAllCargos());
        break;
    }
    default:
        cout << "Invalid strategy selected.\n";
    }
    cout << "Strategy set and scheduling completed.\n";
    pauseForEnter();
}

void TUI::exportSchedule() {
    cout << "\nEnter export file path: ";
    string path;
    getline(cin, path);
    schedulermgr->exportSchedule(path);
    cout << "Schedule exported.\n";
    pauseForEnter();
}

void TUI::viewSchedule() {
    auto matches = schedulermgr->getMatchedList();
    if (matches.empty()) cout << "No matches found.\n";
    else {
        cout << "\nCurrent Matches:\n";
        for (size_t i = 0; i < matches.size(); ++i) {
            auto [freight, cargo, capUsed, capRemain] = matches[i];
            cout << "Match " << (i + 1) << ":\n"
                << " Freight: " << freight << "\n"
                << " Cargo:   " << cargo << "\n"
                << " Capacity Used: " << capUsed
                << ", Capacity Remaining: " << capRemain << "\n";

        }
    }
    pauseForEnter();
}
