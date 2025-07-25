#pragma once

#include <iostream>
#include <limits>
#include <string>

#include "FreightManager.h"
#include "CargoManager.h"
#include "SchedulerManager.h"
#include "FreightFactory.h"
#include "CargoFactory.h"

class TUI {
private:
    iFreightManager* freightmgr;
    iCargoManager* cargomgr;
    iSchedulerManager* schedulermgr;

    // Main Menu Helpers
    void displayMenu();
    int getValidatedChoice();

    // Freight Menu
    void handleFreightMenu();
    void loadFreight();
    void createFreight();
    void addFreight();
    void editFreight();
    void removeFreight();
    void viewAllFreights();

    // Cargo Menu
    void handleCargoMenu();
    void loadCargo();
    void createCargo();
    void addCargo();
    void editCargo();
    void removeCargo();
    void viewAllCargos();

    // Scheduler Menu
    void handleSchedulerMenu();
    void setStrategy();
    void exportSchedule();
    void viewSchedule();

public:
    TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s);
    void welcome();
    void run();
};
