#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
//#include <memory> // Add this include at the top
using namespace std;

#include "TUI.h"



int main() {
    // Create smart pointers for the manager interfaces
    FileHandler fileHandler;
    FreightFactory freightFactory;
    CargoFactory cargoFactory;

    std::unique_ptr<iFreightManager> freightManager =
        std::make_unique<FreightManager>(fileHandler, freightFactory);

    std::unique_ptr<iCargoManager> cargoManager =
        std::make_unique<CargoManager>(fileHandler, cargoFactory);
    std::unique_ptr<iSchedulerManager> schedulerManager = std::make_unique<SchedulerManager>();

    // Pass raw pointers to TUI (if TUI expects raw pointers)
    TUI tui(freightManager.get(), cargoManager.get(), schedulerManager.get());

    // Show welcome and run menu
    tui.run();

    return 0;
}


//int main()
//{
//    // Sample freights
//    std::vector<Freight> testFreights = {
//        Freight("F001", "SG", "09:20AM", FreightType::MiniMover),
//        Freight("F002", "SG", "09:25AM", FreightType::MegaCarrier),
//        Freight("F003", "SG", "09:30AM", FreightType::CargoCruiser)
//    };
//
//    // Sample cargos
//    std::vector<Cargo> testCargos = {
//        Cargo("C001", "SG", "09:15AM", 5),
//        Cargo("C002", "SG", "09:15AM", 4),
//        Cargo("C003", "SG", "09:15AM", 10)
//    };
//
//    // Convert to interface pointers
//    std::vector<iFreight*> freightPtrs;
//    std::vector<iCargo*> cargoPtrs;
//    for (auto& f : testFreights) freightPtrs.push_back(&f);
//    for (auto& c : testCargos) cargoPtrs.push_back(&c);
//
//
//    // Create SchedulerManager and select strategy
//    iSchedulerManager* scheduler = new SchedulerManager();
//
//    // Choose sorting strategy here
//    SortByCapacity sorter;           // Use SortByCapacity sorter; to switch
//    scheduler->setStrategy(&sorter);
//
//    std::cout << "===== Matching Attempts (Sorted) =====\n";
//
//    // Run matching process
//    auto matched = scheduler->createMatchedList(freightPtrs, cargoPtrs);
//
//    // Display results
//    for (const auto& tup : matched) {
//        const auto& freight = std::get<0>(tup);
//        const auto& cargo = std::get<1>(tup);
//        int capLeft = std::get<2>(tup);
//        int cargoCount = std::get<3>(tup);
//        std::cout << "Freight: " << freight.getID() << " (" << freight.getTime() << ") [Capacity left: " << capLeft
//            << ", Cargos assigned: " << cargoCount << "] matched with Cargo: " << cargo.getID() << " (" << cargo.getTime() << ")\n";
//    }
//
//    delete scheduler;
//    return 0;
//}


