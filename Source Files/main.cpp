#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
using namespace std;

#include "SchedulerManager.h"
#include "FreightManager.h"
#include "CargoManager.h"



int main()
{
    // Sample freights
    std::vector<Freight> testFreights = {
        Freight("F001", "SG", "09:30AM", FreightType::MiniMover),
        Freight("F002", "SG", "10:00PM", FreightType::MegaCarrier),
        Freight("F003", "SG", "9:10AM", FreightType::CargoCruiser)
    };

    // Sample cargos
    std::vector<Cargo> testCargos = {
        Cargo("C001", "SG", "09:15AM", 1),
        Cargo("C002", "SG", "09:45PM", 1),
        Cargo("C003", "SG", "09:05AM", 1)
    };

    // Convert to interface pointers
    std::vector<const iFreight*> freightPtrs;
    std::vector<const iCargo*> cargoPtrs;
    for (const auto& f : testFreights) freightPtrs.push_back(&f);
    for (const auto& c : testCargos) cargoPtrs.push_back(&c);

    // Create SchedulerManager and select strategy
    iSchedulerManager* scheduler = new SchedulerManager();

    // Choose sorting strategy here
    SortByCapacity sorter;           // Use SortByCapacity sorter; to switch
    scheduler->setStrategy(&sorter);

    std::cout << "===== Matching Attempts (Sorted) =====\n";

    // Run matching process
    auto matched = scheduler->createMatchedList(freightPtrs, cargoPtrs);

    // Display results
    for (const auto& pair : matched) {
        std::cout << "Freight: " << pair.first.getID() << " (" << pair.first.getTime() << ")"
            << " matched with Cargo: " << pair.second.getID() << " (" << pair.second.getTime() << ")\n";
    }

    delete scheduler;
    return 0;
}

//void showMenu()
//{
//    cout << "=== International Freight Cargo System ===" << endl;
//    cout << "1. Load Freight and Cargo data from files" << endl;
//    cout << "2. Show all Freights" << endl;
//    cout << "3. Show all Cargos" << endl;
//    cout << "4. Run Scheduling" << endl;
//    cout << "5. Export Schedule" << endl;
//    cout << "6. Add/Edit/Delete Freights and Cargos" << endl;
//    cout << "0. Exit" << endl;
//    cout << "Select option: ";
//}
//
//
////int main() {
////    // Create concrete manager instances
////    FreightManager freightManager;
////    CargoManager cargoManager;
////    SchedulerManager schedulerManager;
////
////    // Create TUI object with the managers
////    TUI tui(&freightManager, &cargoManager, &schedulerManager);
////
////    // Show welcome and run menu
////    tui.welcome();
////    tui.run();
////
////    return 0;
////    cout << "=========================\n";
////}
////
////int getValidatedChoice()
////{
////    int choice;
////    while (true)
////    {
////        cout << "Enter your choice: ";
////        cin >> choice;
////        if (cin.fail() || choice < 0 || choice > 3)
////        {
////            cin.clear(); // clear the error flag
////            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
////            cout << "Invalid input. Please enter a number between 0 and 3.\n";
////        }
////        else
////        {
////            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
////            return choice;
////        }
////    }
////
////};
//
//int main()
//{
//    Scheduler scheduler;
//    string freightFile, cargoFile, exportPath;
//
//    bool running = true;
//
//    while (running)
//    {
//        showMenu();
//
//        int choice;
//        cin >> choice;
//        cin.ignore();
//
//        switch (choice)
//        {
//        case 1:
//        {
//            cout << "Please enter your Freight file path: ";
//            getline(cin, freightFile);
//
//            scheduler.loadFreights(freightFile);
//
//            cout << "\nPlease enter your Cargo file path: ";
//            getline(cin, cargoFile);
//
//            scheduler.loadCargos(cargoFile);
//            cout << "\n";
//            break;
//        }
//        case 2:
//        {
//            cout << "\nFreights:" << endl;
//            for (auto freightPtr : scheduler.getFreightManager().getAllRecords())
//            {
//                freightPtr->showDetails();
//            }
//            cout << "\n";
//            break;
//        }
//        case 3:
//        {
//            cout << "\nCargos:" << endl;
//            for (auto cargoPtr : scheduler.getCargoManager().getAllRecords())
//            {
//                cargoPtr->showDetails();
//            }
//            cout << "\n";
//            break;
//        }
//        case 4:
//        {
//            if(scheduler.runScheduling())
//                cout << "\nScheduling completed.\n" << endl;
//            else
//				cout << "\nScheduling could not be completed. Please check your data.\n" << endl;
//            break;
//        }
//        case 5:
//        {
//            cout << "Please state where you want to export your file to: ";
//            getline(cin, exportPath);
//
//            // Strip surrounding quotes if user used them
//            if (!exportPath.empty() && exportPath.front() == '"' && exportPath.back() == '"') {
//                exportPath = exportPath.substr(1, exportPath.size() - 2);
//            }
//
//            scheduler.exportSchedule(exportPath);
//            cout << "Schedule exported to " << exportPath << endl;
//            cout << "\n";
//            break;
//        }
//        case 6:
//        {
//            cout << endl << "1. Add freight\n" << "2. Edit freight by ID\n" << "3. Delete freight by ID\n"
//                << "4. Add cargo\n" << "5. Edit cargo by ID\n" << "6. Delete cargo by ID\n" << "Press any key and then enter to go back to the previous menu\n" << endl;
//            cout << "Select choice: ";
//
//            char subChoice;
//            cin >> subChoice;
//            cin.ignore();
//
//            switch (subChoice) {
//            case '1': {
//                string newId, newLocation, newTime;
//
//                cout << "\nEnter new freight ID, refuel stop and refuelling time: ";
//                cin >> newId >> newLocation >> newTime;
//
//                Freight f = Freight(newId, newLocation, newTime);
//
//                if (scheduler.addFreight(f)) {
//                    cout << "\nFreight " << newId << " added successfully.\n\n";
//                }
//                else {
//                    cout << "\nFreight " << newId << "already exists.\n\n";
//                }
//                break;
//            }
//            case '2': {
//                string currentId, newLocation, newTime;
//
//                cout << "\nEnter freight ID: ";
//                cin >> currentId;
//                scheduler.removeMatchesWithFreightID(currentId);
//                cout << endl << "Enter new refuel stop and refuelling time: ";
//                cin >> newLocation >> newTime;
//
//                Freight updated = Freight(currentId, newLocation, newTime);
//
//                if (scheduler.editFreight(currentId, updated)) {
//                    cout << "\nFreight with ID: " << currentId << " edited successfully.\n\n";
//                }
//                else {
//                    cout << "\nNo freight with ID: " << currentId << " exists.\n\n";
//                }
//                break;
//            }
//            case '3': {
//                string oldId;
//
//                cout << "\nEnter freight ID: ";
//                cin >> oldId;
//
//                if (scheduler.deleteFreight(oldId)) {
//                    cout << "\nFreight with ID: " << oldId << " deleted successfully.\n\n";
//                }
//                else {
//                    cout << "\nNo freight with ID: " << oldId << " exists.\n\n";
//                }
//                break;
//            }
//            case '4': {
//                string newId, newLocation, newTime;
//
//                cout << "\nEnter new cargo ID, destination and arrival time: ";
//                cin >> newId >> newLocation >> newTime;
//
//                Cargo c = Cargo(newId, newLocation, newTime);
//
//                if (scheduler.addCargo(c)) {
//                    cout << "\nCargo " << newId << " added successfully.\n\n";
//                }
//                else {
//                    cout << "\nCargo " << newId << "already exists.\n\n";
//                }
//                break;
//            }
//            case '5': {
//                string currentId, newLocation, newTime;
//
//                cout << "\nEnter cargo ID: ";
//                cin >> currentId;
//                scheduler.removeMatchesWithCargoID(currentId);
//                cout << endl << "Enter new destination and arrival time: ";
//                cin >> newLocation >> newTime;
//
//                Cargo updated = Cargo(currentId, newLocation, newTime);
//
//                if (scheduler.editCargo(currentId, updated)) {
//                    cout << "\nCargo with ID: " << currentId << " edited successfully.\n\n";
//                }
//                else {
//                    cout << "\nNo cargo with ID: " << currentId << " exists.\n\n";
//                }
//                break;
//            }
//            case '6': {
//                string oldId;
//
//                cout << "\nEnter cargo ID: ";
//                cin >> oldId;
//
//                if (scheduler.deleteCargo(oldId)) {
//                    cout << "\nCargo with ID: " << oldId << " deleted successfully.\n\n";
//                }
//                else {
//                    cout << "\nNo Cargo with ID: " << oldId << " exists.\n\n";
//                }
//                break;
//            }
//            default: {
//                break;
//            }
//            }
//            break;
//        }
//        case 0:
//        {
//            running = false;
//            break;
//        }
//        default:
//        {
//            cout << "Invalid option. Try again.\n" << endl;
//            break;
//        }
//        }
//    }
//
//    cout << "Exiting application." << endl;
//    return 0;
//}
