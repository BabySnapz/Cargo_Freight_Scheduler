#include <iostream>
#include <thread>   
#include <chrono>
#include "TUI.h"

using namespace std;

/****************** Constructor ***********************************/
TUI::TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s)
    : freightmgr(f), cargomgr(c), schedulermgr(s) {}

void TUI::welcome()
{
    cout << "=========================================\n";
    cout << "Welcome to the Freight Management System!\n";
    cout << "=========================================\n";
}


/****************** Main Run Loop ********************************/
void TUI::run()
{
    int choice;
    bool exit_menu = false;

    welcome();

    while (!exit_menu) {
        displayMenu();
        choice = getValidatedChoice(); // handles validation

        switch (choice) {
        case 1:
            showFreightOptions();
            break;
        case 2:
            showCargoOptions();
            break;
        case 3:
            showScheduleOptions();
            break;
        case 0: // Exit program
            std::cout << "Exiting program.\n";
            exit_menu = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    }
}


/****************** Menu Display **********************************/
void TUI::displayMenu()
{
    cout << "\n=== Main Menu ===\n";
    cout << "1. Freight Management\n";
    cout << "2. Cargo Management\n";
    cout << "3. Scheduler Management\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

/****************** Welcome Screen ********************************/
void TUI::welcome() {
    system("CLS");
    cout << "===========================================\n";
    cout << "**       Welcome to Freight System       **\n";
    cout << "===========================================\n";
    system("pause");
}
int TUI::getValidatedChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        if (cin >> choice) {
            return choice;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/****************** Freight Menu **********************************/
void showFreightOptions() {
    int choice;
    int getValidatedChoice(); // Call to validate input
    do {
        cout << "\n--- Freight Options ---\n";
        cout << "1. Create Freight\n";
        cout << "2. Add Freight\n";
        cout << "3. Edit Freight\n";
        cout << "4. Remove Freight\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";

        choice = getValidatedChoice();

        switch (choice) {
        case 1:
            freightmgr->createFreight();
            break;
        case 2:
            freightmgr->addFreight();
            break;
        case 3:
            freightmgr->editFreights();
            break;
        case 4:
            freightmgr->removeFreight();
            break;
        case 0:
            break;
        default:
            cout << "Invalid input. Please try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    } while (choice != 0);
}

/****************** Scheduler Menu *******************************/
void TUI::showScheduleOptions() {
    int choice;
    choice = getValidatedChoice();
    bool exitMenu = false;

    while (!exitMenu) {
        system("CLS");
        cout << "--- Scheduler Menu ---\n";
        cout << "1. Schedule Freight\n";
        cout << "2. Export Schedule\n";
        cout << "3. View Schedule\n";
        cout << "4. Cancel Schedule\n";
        cout << "0. Back to Main Menu\n";

        choice = getValidatedChoice();

        switch (choice) {
        case 1:
            schedulermgr->scheduleFreight();
            break;
        case 2:
            schedulermgr->exportSchedule();
            break;
        case 3:
            schedulermgr->viewSchedule();
            break;
        case 4:
            schedulermgr->cancelSchedule();
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            cout << "Invalid option. Try again.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

