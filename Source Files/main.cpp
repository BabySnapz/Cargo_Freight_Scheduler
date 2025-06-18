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
    cout << "6. Add/Edit/Delete Freights and Cargos (Not implemented here)" << endl;
    cout << "0. Exit" << endl;
    cout << "Select option: ";
}

int main()
{
    Scheduler scheduler;
    string freightFile, cargoFile;
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
           
            freightFile = "freight.txt";
            cargoFile = "cargo.txt";

            scheduler.loadFreights(freightFile);
            scheduler.loadCargos(cargoFile);
            cout << "\n";
            break;
        }
        case 2:
        {
            cout << "Freights:" << endl;
            for (auto freightPtr : scheduler.getFreightManager().getAllRecords())
            {
                freightPtr->showDetails();
            }
            cout << "\n";   
            break;
        }
        case 3:
        {
            cout << "Cargos:" << endl;
            for (auto cargoPtr : scheduler.getCargoManager().getAllRecords())
            {
                cargoPtr->showDetails();
            }
            cout << "\n";
            break;
        }
        case 4:
        {
            scheduler.runScheduling();
            cout << "Scheduling completed.\n" << endl;

            break;
        }
        case 5:
        {
            string exportPath;

            exportPath = "schedule.txt";
            scheduler.exportSchedule(exportPath);
            cout << "Schedule exported to " << exportPath << endl;
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << endl << "1. Add freight\n" << "2. Edit freight by ID\n" << "3. Delete freight by ID\n" 
                << "4. Add cargo\n" << "5. Edit cargo by ID\n" << "6. Delete cargo by ID\n" << endl;
            cout << "Select choice: ";

            int subChoice;
            cin >> subChoice;
            cin.ignore();

            switch (subChoice) {
                case 1:{
                    string newId, newLocation, newTime;

                    cout << "\nEnter new freight ID, refuel stop and refuelling time: ";   
                    cin >> newId >> newLocation >> newTime;

                    Freight* f = new Freight(newId, newLocation, newTime);

                    if (scheduler.getFreightManager().addRecord(f)) {
                        cout << "\nFreight " << newId << " added successfully.\n\n";
                    }
                    else {
                        cout << "\nFreight " << newId << "already exists.\n\n";
                    }
                    break;
                   }
                case 2:{
                    string currentId, newLocation, newTime;

                    cout << "\nEnter freight ID: ";
                    cin >> currentId;
                    cout << endl << "Enter new refuel stop and refuelling time: ";
                    cin >> newLocation >> newTime;

                    Freight* updated = new Freight(currentId, newLocation, newTime);

                    if (scheduler.getFreightManager().editRecord(currentId, updated)) {
                        cout << "\nFreight with ID: " << currentId << " edited successfully.\n\n";
                    }
                    else {
                        cout << "\nNo freight with ID: " << currentId << " exists.\n\n";
                    }
                    break;
                }
                case 3:{
                    string oldId;

                    cout << "\nEnter freight ID: ";
                    cin >> oldId;

                    if (scheduler.getFreightManager().deleteRecord(oldId)) {
                        cout << "\nFreight with ID: " << oldId << " deleted successfully.\n\n";
                    }
                    else {
                        cout << "\nNo freight with ID: " << oldId << " exists.\n\n";
                    }
                    break;
                }
                case 4:{
                    string newId, newLocation, newTime;

                    cout << "\nEnter new cargo ID, destination and arrival time: ";
                    cin >> newId >> newLocation >> newTime;

                    Cargo* c = new Cargo(newId, newLocation, newTime);

                    if (scheduler.getCargoManager().addRecord(c)) {
                        cout << "\nCargo " << newId << " added successfully.\n\n";
                    }
                    else {
                        cout << "\nCargo " << newId << "already exists.\n\n";
                    }
                    break;
                }
                case 5:{
                    string currentId, newLocation, newTime;

                    cout << "\nEnter cargo ID: ";
                    cin >> currentId;
                    cout << endl << "Enter new destination and arrival time: ";
                    cin >> newLocation >> newTime;

                    Cargo* updated = new Cargo(currentId, newLocation, newTime);

                    if (scheduler.getCargoManager().editRecord(currentId, updated)) {
                        cout << "\nCargo with ID: " << currentId << " edited successfully.\n\n";
                    }
                    else {
                        cout << "\nNo cargo with ID: " << currentId << " exists.\n\n";
                    }
                    break;
                }
                case 6:{
                    string oldId;

                    cout << "\nEnter cargo ID: ";
                    cin >> oldId;

                    if (scheduler.getCargoManager().deleteRecord(oldId)) {
                        cout << "\nCargo with ID: " << oldId << " deleted successfully.\n\n";
                    }
                    else {
                        cout << "\nNo Cargo with ID: " << oldId << " exists.\n\n";
                    }
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
