#ifndef TUI_H
#define TUI_H

#include <iostream>
#include <limits> // For input validation

#include "FreightManager.h"
#include "CargoManager.h"
#include "SchedulerManager.h"

using namespace std;

class TUI {
private:
    iFreightManager* freightmgr;
    iCargoManager* cargomgr;
    iSchedulerManager* schedulermgr;
    void displayMenu();
    int getValidatedChoice();
    void showFreightOptions();
    void showCargoOptions();
    void showScheduleOptions();

public:
    TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s);
    void welcome();
    void run();

    
};

#endif // TUI_H
