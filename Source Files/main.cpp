#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

#include "Scheduler.h"

void showMenu()
{
    cout << "=== International Freight Cargo System ===" << endl;
    cout << "1. Load Freight and Cargo data from files" << endl;
    cout << "2. Show all Freights" << endl;
    cout << "3. Show all Cargos" << endl;
    cout << "4. Run Scheduling" << endl;
    cout << "5. Export Schedule" << endl;
    cout << "6. Add/Edit/Delete Freights and Cargos" << endl;
    cout << "0. Exit" << endl;
    cout << "Select option: ";
}

int main()
{
    Scheduler scheduler;
    string freightFile, cargoFile, exportPath;

    bool running = true;

    while (running)
    {
        showMenu();

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "Please enter your Freight file path: ";
            getline(cin, freightFile);

            scheduler.loadFreights(freightFile);

            cout << "\nPlease enter your Cargo file path: ";
            getline(cin, cargoFile);

            scheduler.loadCargos(cargoFile);
            cout << "\n";
            break;
        }
        case 2:
        {
            cout << "\nFreights:" << endl;
            for (auto freightPtr : scheduler.getFreightManager().getAllRecords())
            {
                freightPtr->showDetails();
            }
            cout << "\n";
            break;
        }
        case 3:
        {
            cout << "\nCargos:" << endl;
            for (auto cargoPtr : scheduler.getCargoManager().getAllRecords())
            {
                cargoPtr->showDetails();
            }
            cout << "\n";
            break;
        }
        case 4:
        {
            if(scheduler.runScheduling())
                cout << "\nScheduling completed.\n" << endl;
            else
				cout << "\nScheduling could not be completed. Please check your data.\n" << endl;
            break;
        }
        case 5:
        {
            cout << "Please state where you want to export your file to: ";
            getline(cin, exportPath);

            // Strip surrounding quotes if user used them
            if (!exportPath.empty() && exportPath.front() == '"' && exportPath.back() == '"') {
                exportPath = exportPath.substr(1, exportPath.size() - 2);
            }

            scheduler.exportSchedule(exportPath);
            cout << "Schedule exported to " << exportPath << endl;
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << endl << "1. Add freight\n" << "2. Edit freight by ID\n" << "3. Delete freight by ID\n"
                << "4. Add cargo\n" << "5. Edit cargo by ID\n" << "6. Delete cargo by ID\n" << "Press any key and then enter to go back to the previous menu\n" << endl;
            cout << "Select choice: ";

            char subChoice;
            cin >> subChoice;
            cin.ignore();

            switch (subChoice) {
            case '1': {
                string newId, newLocation, newTime;

                cout << "\nEnter new freight ID, refuel stop and refuelling time: ";
                cin >> newId >> newLocation >> newTime;

                Freight f = Freight(newId, newLocation, newTime);

                if (scheduler.addFreight(f)) {
                    cout << "\nFreight " << newId << " added successfully.\n\n";
                }
                else {
                    cout << "\nFreight " << newId << "already exists.\n\n";
                }
                break;
            }
            case '2': {
                string currentId, newLocation, newTime;

                cout << "\nEnter freight ID: ";
                cin >> currentId;
                scheduler.removeMatchesWithFreightID(currentId);
                cout << endl << "Enter new refuel stop and refuelling time: ";
                cin >> newLocation >> newTime;

                Freight updated = Freight(currentId, newLocation, newTime);

                if (scheduler.editFreight(currentId, updated)) {
                    cout << "\nFreight with ID: " << currentId << " edited successfully.\n\n";
                }
                else {
                    cout << "\nNo freight with ID: " << currentId << " exists.\n\n";
                }
                break;
            }
            case '3': {
                string oldId;

                cout << "\nEnter freight ID: ";
                cin >> oldId;

                if (scheduler.deleteFreight(oldId)) {
                    cout << "\nFreight with ID: " << oldId << " deleted successfully.\n\n";
                }
                else {
                    cout << "\nNo freight with ID: " << oldId << " exists.\n\n";
                }
                break;
            }
            case '4': {
                string newId, newLocation, newTime;

                cout << "\nEnter new cargo ID, destination and arrival time: ";
                cin >> newId >> newLocation >> newTime;

                Cargo c = Cargo(newId, newLocation, newTime);

                if (scheduler.addCargo(c)) {
                    cout << "\nCargo " << newId << " added successfully.\n\n";
                }
                else {
                    cout << "\nCargo " << newId << "already exists.\n\n";
                }
                break;
            }
            case '5': {
                string currentId, newLocation, newTime;

                cout << "\nEnter cargo ID: ";
                cin >> currentId;
                scheduler.removeMatchesWithCargoID(currentId);
                cout << endl << "Enter new destination and arrival time: ";
                cin >> newLocation >> newTime;

                Cargo updated = Cargo(currentId, newLocation, newTime);

                if (scheduler.editCargo(currentId, updated)) {
                    cout << "\nCargo with ID: " << currentId << " edited successfully.\n\n";
                }
                else {
                    cout << "\nNo cargo with ID: " << currentId << " exists.\n\n";
                }
                break;
            }
            case '6': {
                string oldId;

                cout << "\nEnter cargo ID: ";
                cin >> oldId;

                if (scheduler.deleteCargo(oldId)) {
                    cout << "\nCargo with ID: " << oldId << " deleted successfully.\n\n";
                }
                else {
                    cout << "\nNo Cargo with ID: " << oldId << " exists.\n\n";
                }
                break;
            }
            default: {
                break;
            }
            }
            break;
        }
        case 0:
        {
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid option. Try again.\n" << endl;
            break;
        }
        }
    }

    cout << "Exiting application." << endl;
    return 0;
}
