#include <iostream>
#include <thread>   
#include <chrono>
#include "TUI.h"
#include "FreightManager.h"
#include "CargoManager.h"
#include "SchedulerManager.h"
#include "FileHandler.h"

using namespace std;


TUI::TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s)
    : freightmgr(f), cargomgr(c), schedulermgr(s) {
}

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

void TUI::displayMenu()
{
    cout << "\n=== Main Menu ===\n";
    cout << "1. Freight Management\n";
    cout << "2. Cargo Management\n";
    cout << "3. Scheduler Management\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

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
void TUI::showFreightOptions() {
    int choice;
    bool exitMenu = false;

    while (!exitMenu) {
        // Display Freight Menu
        std::cout << "--- Freight Menu ---\n";
        std::cout << "1. Load Freight data from file\n";
        std::cout << "2. Create Freight\n";
        std::cout << "3. Add Freight\n";
        std::cout << "4. Edit Freight\n";
        std::cout << "5. Remove Freight\n";
        std::cout << "6. View All Freights\n";
        std::cout << "0. Back to Main Menu\n";

        choice = getValidatedChoice();


        switch (choice) {
        case 1: {
            std::string filepath;
            std::cout << "\n=== Load Freight Data from File ===\n";
            std::cout << "Enter file path: ";
            std::cin.ignore();
            std::getline(std::cin, filepath);
            

            if (!filepath.empty() && filepath.front() == '"' && filepath.back() == '"') {
                filepath = filepath.substr(1, filepath.length() - 2);
            }

            if (freightmgr->loadFromFile(filepath)) {
                std::cout << "\n File loaded successfully!\n";
                std::vector<iFreight*> freights = freightmgr->getAllFreights();

                if (freights.empty()) {
                    std::cout << "\n No freight records loaded from the file.\n";
                }
                else {
                    std::cout << "\n=== Loaded Freight Records (" << freights.size() << " items) ===\n";
                    std::cout << std::string(70, '-') << "\n";

                    for (size_t i = 0; i < freights.size(); ++i) {
                        std::cout << "[" << (i + 1) << "] ";

                        // Use overloaded << operator (most common approach)
                        std::cout << *freights[i] << "\n";

                        // Alternative: Manual output using getter methods
                        // std::cout << "ID: " << freights[i]->getID() 
                        //           << ", Location: " << freights[i]->getLocation()
                        //           << ", Time: " << freights[i]->getTime() 
                        //           << ", Type: " << freights[i]->getFreightType() << "\n";

                        if ((i + 1) % 5 == 0 && i < freights.size() - 1) {
                            std::cout << std::string(70, '-') << "\n";
                        }
                    }
                    std::cout << std::string(70, '-') << "\n";
                }
            }
            else {
                std::cout << "\n? Failed to load file. Please check the file path and permissions.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;

        }

        case 2: {
            std::string id, location, time;
            int typeChoice;
            FreightType type;

            std::cout << "Enter Freight ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Location: ";
            std::getline(std::cin, location);
            std::cout << "Enter Time: ";
            std::getline(std::cin, time);
            std::cout << "Select Freight Type (1 = MiniMover, 2 = CargoCruiser, 3 = MegaCarrier): ";
            std::cin >> typeChoice;
            std::cin.ignore();

            switch (typeChoice)
            {
            case 1:
                type = FreightType::MiniMover;
                break;
            case 2:
                type = FreightType::CargoCruiser;
                break;
            case 3:
                type = FreightType::MegaCarrier;
                break;
            default:
                std::cout << "Invalid type selected. Defaulting to MiniMover.\n";
                type = FreightType::MiniMover;
            }

            freightmgr->createFreight(id, location, time, type);
            break;
        }

        case 3: {
            std::string id, location, time;
            int typeChoice;
            FreightType type;

            std::cout << "Enter Freight ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter Location: ";
            std::getline(std::cin, location);
            std::cout << "Enter Time: ";
            std::getline(std::cin, time);
            std::cout << "Select Freight Type (1 = MiniMover, 2 = CargoCruiser, 3 = MegaCarrier): ";
            std::cin >> typeChoice;
            std::cin.ignore();

            switch (typeChoice) {
            case 1: type = FreightType::MiniMover; break;
            case 2: type = FreightType::CargoCruiser; break;
            case 3: type = FreightType::MegaCarrier; break;
            default:
                std::cout << "Invalid type selected. Defaulting to MiniMover.\n";
                type = FreightType::MiniMover;
            }

            FreightParams params;
            params.setID(id)
                .setLocation(location)
                .setTime(time)
                .setFreightType(type);

            std::unique_ptr<Freight> freight = std::make_unique<Freight>(
                params.getID(), params.getLocation(), params.getTime(), params.getFreightType());
            freightmgr->addFreight(std::move(freight));
            break;
        }

        case 4: {
            std::string id, newLocation, newTime;
            int typeChoice;
            FreightType type;

            std::cout << "Enter ID of freight to edit: ";
            std::getline(std::cin, id);
            std::cout << "Enter new Location: ";
            std::getline(std::cin, newLocation);
            std::cout << "Enter new Time: ";
            std::getline(std::cin, newTime);
            std::cout << "Select Freight Type (1 = MiniMover, 2 = CargoCruiser, 3 = MegaCarrier): ";
            std::cin >> typeChoice;
            std::cin.ignore();

            switch (typeChoice) {
            case 1: type = FreightType::MiniMover; break;
            case 2: type = FreightType::CargoCruiser; break;
            case 3: type = FreightType::MegaCarrier; break;
            default:
                std::cout << "Invalid type selected. Defaulting to MiniMover.\n";
                type = FreightType::MiniMover;
            }

            FreightParams params;
            params.setLocation(newLocation)
                .setTime(newTime)
                .setFreightType(type);

            freightmgr->editFreight(id, params);
            break;
        }

        case 5: {
            std::string id;
            std::cout << "Enter ID of freight to remove: ";
            std::getline(std::cin, id);
            freightmgr->removeFreight(id);
            break;
        }
        case 6: {
            std::cout << "\n=== All Freight Records ===\n";

            try {
                std::vector<iFreight*> freights = freightmgr->getAllFreights();

                if (freights.empty()) {
                    std::cout << "\n? No freight records available.\n";
                }
                else {
                    std::cout << std::string(70, '-') << "\n";
                    std::cout << "Total Records: " << freights.size() << "\n";
                    std::cout << std::string(70, '-') << "\n";

                    for (size_t i = 0; i < freights.size(); ++i) {
                        std::cout << "[" << (i + 1) << "] ";

                        // Use overloaded << operator instead of toString()
                        std::cout << *freights[i] << "\n";

                        // Alternative if no << operator - use getter methods:
                        // std::cout << "ID: " << freights[i]->getID() 
                        //           << ", Location: " << freights[i]->getLocation()
                        //           << ", Time: " << freights[i]->getTime() 
                        //           << ", Type: " << freights[i]->getFreightType() << "\n";

                        if ((i + 1) % 5 == 0 && i < freights.size() - 1) {
                            std::cout << std::string(70, '-') << "\n";
                        }
                    }
                    std::cout << std::string(70, '-') << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "\n? Failed to retrieve freight records: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;

        case 0:
            exitMenu = true;
            break;

        default:
            std::cout << "Invalid option. Try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        }
    }
}
/****************** Cargo Menu **********************************/
void TUI::showCargoOptions() {
    int choice;
    bool exitMenu = false;
    system("CLS"); // Clear the console for better readability
    while (!exitMenu) {
        

        cout << "\n--- Cargo Menu ---\n";
        cout << "1. Load Cargo data from file\n";
        cout << "2. Add Cargo\n";
        cout << "3. Create Cargo\n";
        cout << "4. Edit Cargo\n";
        cout << "5. Delete Cargo\n";
        cout << "6. View All Cargos\n";
        cout << "0. Back to Main Menu\n";

        
        choice = getValidatedChoice();

        switch (choice)
        {
        case 1:
        {
            std::string filepath;
            std::cout << "\n=== Load Cargo Data from File ===\n";
            std::cout << "Enter file path: ";
            std::cin.ignore();
            std::getline(std::cin, filepath);
           

            if (!filepath.empty() && filepath.front() == '"' && filepath.back() == '"') {
                filepath = filepath.substr(1, filepath.length() - 2);
            }

            if (cargomgr->loadFromFile(filepath))
            {
                std::cout << "\n File loaded successfully!\n";
                std::vector<iCargo*> cargos = cargomgr->getAllCargos();

                if (cargos.empty())
                {
                    std::cout << "\nNo cargo records loaded from the file.\n";
                }
                else
                {
                    std::cout << "\n=== Loaded Cargo Records (" << cargos.size() << " items) ===\n";
                    std::cout << std::string(70, '-') << "\n";

                    for (size_t i = 0; i < cargos.size(); ++i)
                    {
                        std::cout << "[" << (i + 1) << "] ";
                        std::cout << *cargos[i]; // Uses the overloaded << operator from Cargo.h

                        if ((i + 1) % 5 == 0 && i < cargos.size() - 1)
                        {
                            std::cout << std::string(70, '-') << "\n";
                        }
                    }
                    std::cout << std::string(70, '-') << "\n";
                }
            }
            else
            {
                std::cout << "\nFailed to load file. Please check the file path and permissions.\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;

        }

        case 2:
        {
            std::string id, location, time;
            int cargoGrouping;

            std::cout << "\n=== Create New Cargo Record ===\n";

            std::cout << "Enter Cargo ID: ";
            std::getline(std::cin, id);

            std::cout << "Enter Location: ";
            std::getline(std::cin, location);

            std::cout << "Enter Time: ";
            std::getline(std::cin, time);

            std::cout << "Enter Cargo Grouping (integer): ";
            std::cin >> cargoGrouping;
            std::cin.ignore();

            try
            {
                cargomgr->createCargo(id, location, time, cargoGrouping);
                std::cout << "\nCargo record created successfully!\n";
                std::cout << "ID: " << id << " | Location: " << location
                    << " | Time: " << time << " | Grouping: " << cargoGrouping << "\n";
            }
            catch (const std::exception& e)
            {
                std::cout << "\nFailed to create cargo record: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }
        case 3:
        {
            std::string id, location, time;
            int cargoGrouping;

            std::cout << "\n=== Add New Cargo ===\n";

            std::cout << "Enter Cargo ID: ";
            std::getline(std::cin, id);

            std::cout << "Enter Location: ";
            std::getline(std::cin, location);

            std::cout << "Enter Time: ";
            std::getline(std::cin, time);

            std::cout << "Enter Cargo Grouping (integer): ";
            std::cin >> cargoGrouping;
            std::cin.ignore();

            try
            {
                std::unique_ptr<Cargo> cargo = std::make_unique<Cargo>(id, location, time, cargoGrouping);
                cargomgr->addCargo(std::move(cargo));
                std::cout << "\n? Cargo added successfully!\n";
                std::cout << "ID: " << id << " | Location: " << location
                    << " | Time: " << time << " | Grouping: " << cargoGrouping << "\n";
            }
            catch (const std::exception& e)
            {
                std::cout << "\nFailed to add cargo: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 4: {
            std::string id, newLocation, newTime;
            int newCargoGrouping;

            std::cout << "\n=== Edit Cargo ===\n";

            // First, check if cargo exists and display current values
            std::vector<iCargo*> allCargos = cargomgr->getAllCargos();
            auto cargoIt = std::find_if(allCargos.begin(), allCargos.end(),
                [](iCargo* cargo) { return false; }); // Will be replaced with actual ID check

            std::cout << "Enter ID of cargo to edit: ";
            std::getline(std::cin, id);

            // Display current cargo info if found
            bool cargoFound = false;
            for (const auto& cargo : allCargos) {
                if (cargo->getID() == id) {
                    std::cout << "\nCurrent cargo details:\n";
                    std::cout << "ID: " << cargo->getID() << "\n";
                    std::cout << "Location: " << cargo->getLocation() << "\n";
                    std::cout << "Time: " << cargo->getTime() << "\n";
                    std::cout << "Grouping: " << cargo->getCargoGrouping() << "\n";
                    std::cout << std::string(40, '-') << "\n";
                    cargoFound = true;
                    break;
                }
            }

            if (!cargoFound) {
                std::cout << "\nCargo with ID '" << id << "' not found.\n";
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                break;
            }

            std::cout << "Enter new Location: ";
            std::getline(std::cin, newLocation);

            std::cout << "Enter new Time: ";
            std::getline(std::cin, newTime);

            std::cout << "Enter new Cargo Grouping: ";
            std::cin >> newCargoGrouping;
            std::cin.ignore();

            try {
                // Create CargoParams object (assuming it implements iRecordParams)
                CargoParams params;
                params.setLocation(newLocation)
                    .setTime(newTime)
                    .setCargoGrouping(newCargoGrouping);

                if (cargomgr->editCargo(id, params)) {
                    std::cout << "\nCargo edited successfully!\n";
                    std::cout << "ID: " << id << " | New Location: " << newLocation
                        << " | New Time: " << newTime << " | New Grouping: " << newCargoGrouping << "\n";
                }
                else {
                    std::cout << "\nFailed to edit cargo with ID '" << id << "'.\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "\nFailed to edit cargo: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 5: {
            std::string id;

            std::cout << "\n=== Remove Cargo ===\n";
            std::cout << "Enter ID of cargo to remove: ";
            std::getline(std::cin, id);

            try {
                if (cargomgr->removeCargo(id)) {
                    std::cout << "\n? Cargo with ID '" << id << "' removed successfully!\n";
                }
                else {
                    std::cout << "\n? Cargo with ID '" << id << "' not found.\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "\n? Failed to remove cargo: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 6:
        {
            std::cout << "\n=== All Cargo Records ===\n";

            try {
                std::vector<iCargo*> cargos = cargomgr->getAllCargos();

                if (cargos.empty())
                {
                    std::cout << "\nNo cargo records available.\n";
                }
                else {
                    std::cout << std::string(70, '-') << "\n";
                    std::cout << "Total Records: " << cargos.size() << "\n";
                    std::cout << std::string(70, '-') << "\n";

                    for (size_t i = 0; i < cargos.size(); ++i) {
                        std::cout << "[" << (i + 1) << "] ";
                        std::cout << *cargos[i]; // Uses the overloaded << operator

                        if ((i + 1) % 5 == 0 && i < cargos.size() - 1) {
                            std::cout << std::string(70, '-') << "\n";
                        }
                    }
                    std::cout << std::string(70, '-') << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "\nFailed to retrieve cargo records: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 0:
            exitMenu = true;
            break;

        default:
            std::cout << "Invalid option. Try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}


/****************** Scheduler Menu *******************************/
void TUI::showScheduleOptions() {
    int choice, strategyOption;
    bool exitMenu = false;
    system("CLS");

    while (!exitMenu) {
        
        std::cout << "\n=== Scheduler Management System ===\n";
        std::cout << "1. Set Scheduling Strategy\n";
        std::cout << "2. Export Schedule to File\n";
        std::cout << "3. View Current Schedule\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << std::string(40, '-') << "\n";

        choice = getValidatedChoice();

        switch (choice) {
        case 1: {
            std::cout << "\n=== Set Scheduling Strategy ===\n";
            std::cout << "Available Strategies:\n";
            std::cout << "1. sortByTime\n";
            std::cout << "2. sortByCapacity\n";
            std::unique_ptr<SortAlgorithms> strategy;

            try
            {
                std::cin >> strategyOption;
                std::cin.ignore(); // Clear newline character from input buffer
                switch (strategyOption)
                {
                case 1:
                    strategy = std::make_unique<SortByTime>();
                    break;
                case 2:
                    strategy = std::make_unique<SortByCapacity>();
                    break;
                default:
                    std::cout << "Please enter a valid input" << std::endl;
                    return;
                }

                schedulermgr->setStrategy(strategy.get());
                auto matched = schedulermgr->createMatchedList(freightmgr->getAllFreights(), cargomgr->getAllCargos());

                if (matched.empty()) {
                    std::cout << "No matches found.\n";
                }
                else {
                    for (const auto& [freight, cargo, remaining, used] : matched) {
                        std::cout << "Matched Freight " << freight.getID()
                            << " with Cargo " << cargo.getID()
                            << " | Used Capacity: " << used
                            << " | Remaining Freight Capacity: " << remaining << "\n";
                    }
                }



                std::cout << "\nScheduling strategy set successfully!\n";
            }
            catch (const std::exception& e) {
                std::cout << "\nFailed to set strategy: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 2: {
            std::string filepath;
            std::cout << "\n=== Export Schedule to File ===\n";
            std::cout << "Enter file path for export: ";
            std::getline(std::cin, filepath);

            try {
                schedulermgr->exportSchedule(filepath);
                std::cout << "\nSchedule exported successfully to: " << filepath << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "\nFailed to export schedule: " << e.what() << "\n";
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 3: {
            std::cout << "\n=== Current Schedule ===\n";

            try {
                std::vector<std::tuple<const iFreight&, const iCargo&, int, int>> matchedTuples =
                    schedulermgr->getMatchedList();

                if (matchedTuples.empty()) {
                    std::cout << "\nNo freight-cargo matches scheduled.\n";
                }
                else {
                    std::cout << std::string(80, '-') << "\n";
                    std::cout << "Total Matches: " << matchedTuples.size() << "\n";
                    std::cout << std::string(80, '-') << "\n";

                    for (size_t i = 0; i < matchedTuples.size(); ++i) {
                        const auto& freight = std::get<0>(matchedTuples[i]);
                        const auto& cargo = std::get<1>(matchedTuples[i]);
                        int capacityLeft = std::get<2>(matchedTuples[i]);
                        int cargoCount = std::get<3>(matchedTuples[i]);

                        std::cout << "\n[Match " << (i + 1) << "]\n";
                        std::cout << "Freight: " << freight.getID()
                            << " (" << freight.getTime() << ") "
                            << "[Capacity left: " << capacityLeft
                            << ", Cargos assigned: " << cargoCount << "]\n";
                        std::cout << "Cargo:   " << cargo.getID()
                            << " (" << cargo.getTime() << ")\n";

                        if ((i + 1) % 3 == 0 && i < matchedTuples.size() - 1) {
                            std::cout << std::string(80, '-') << "\n";
                        }
                    }

                    std::cout << std::string(80, '-') << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "\nFailed to retrieve schedule: " << e.what() << "\n";
            }


            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            break;
        }

        case 0:
            exitMenu = true;
            break;

        default:
            std::cout << "\nInvalid option. Please try again.\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
    }
}