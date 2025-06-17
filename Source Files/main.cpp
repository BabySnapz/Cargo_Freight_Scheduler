#include <iostream>
#include <string>

#include "Scheduler.h"

using namespace std;

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
            /*cout << "Enter path for freight data file: ";
            getline(cin, freightFile);
            cout << "Enter path for cargo data file: ";
            getline(cin, cargoFile);*/

            freightFile = "freight.txt";
            cargoFile = "cargo.txt";

            scheduler.loadFreights(freightFile);
            scheduler.loadCargos(cargoFile);
            //cout << "Data loaded successfully." << endl;
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

            /*cout << "Enter path to export schedule: ";
            getline(cin, exportPath);*/

            exportPath = "schedule.txt";
            scheduler.exportSchedule(exportPath);
            cout << "Schedule exported to " << exportPath << endl;
            cout << "\n";
            break;
        }
        case 6:
        {
            cout << "Add/Edit/Delete feature not implemented in this demo.\n" << endl;
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
