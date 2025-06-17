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
            cout << "Enter path for freight data file: ";
            getline(cin, freightFile);
            cout << "Enter path for cargo data file: ";
            getline(cin, cargoFile);

            scheduler.loadFreights(freightFile);
            scheduler.loadCargos(cargoFile);
            //cout << "Data loaded successfully." << endl;
            break;
        }
        case 2:
        {
            cout << "Freights:" << endl;
            for (auto freightPtr : scheduler.getFreightManager().getAllRecords())
            {
                freightPtr->showDetails();
            }
            break;
        }
        case 3:
        {
            cout << "Cargos:" << endl;
            for (auto cargoPtr : scheduler.getCargoManager().getAllRecords())
            {
                cargoPtr->showDetails();
            }
            break;
        }
        case 4:
        {
            scheduler.runScheduling();
            cout << "Scheduling completed." << endl;
            break;
        }
        case 5:
        {
            cout << "Enter path to export schedule: ";
            string exportPath;
            getline(cin, exportPath);
            scheduler.exportSchedule(exportPath);
            cout << "Schedule exported to " << exportPath << endl;
            break;
        }
        case 6:
        {
            cout << "Add/Edit/Delete feature not implemented in this demo." << endl;
            break;
        }
        case 0:
        {
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid option. Try again." << endl;
            break;
        }
        }
    }

    cout << "Exiting application." << endl;
    return 0;
}
