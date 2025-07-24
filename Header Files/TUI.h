#ifndef TUI_H
#define TUI_H

#include <iostream>
#include <limits> // For input validation

class iFreightManager;
class iCargoManager;
class iSchedulerManager;

using namespace std;

class TUI {
private:
    iFreightManager* freightmgr;
    iCargoManager* cargomgr;
    iSchedulerManager* schedulermgr;

public:
    TUI(iFreightManager* f, iCargoManager* c, iSchedulerManager* s)
        : freightmgr(f), cargomgr(c), schedulermgr(s) {}
    void welcome();
    void run();

private:
    void displayMenu();
    int getValidatedChoice();
    void showFreightOptions();
    void showCargoOptions();
    void showScheduleOptions();
};

#endif // TUI_H
