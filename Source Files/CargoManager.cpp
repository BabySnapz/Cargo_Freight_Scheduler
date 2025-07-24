#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

#include "CargoManager.h"

//Records* CargoManager::makeRecord(const string& id, const string& refuelStop, const string& refuelTime) {
//    return new Cargo(id, refuelStop, refuelTime);
//}



bool CargoManager::addCargo(std::unique_ptr<Cargo> cargo)
{
    cargos.push_back(std::move(cargo));
    return true;
}

bool CargoManager::createCargo(const std::string& id, const std::string& location,
    const std::string& time, int cargoGrouping)
{
    // Create the params using CargoFactory
    auto cargoParams = std::make_unique<CargoParams>();
    cargoParams->setID(id)
        .setLocation(location)
        .setTime(time)
        .setCargoGrouping(cargoGrouping);

    // Create the Cargo object using the factory
    auto cargo = std::unique_ptr<Cargo>(static_cast<Cargo*>(c_Factory.create(*cargoParams).release()));

    // Add the created cargo to the vector
    return addCargo(std::move(cargo));
}

bool CargoManager::editCargo(const std::string& id, const iRecordParams& params)
{
    auto it = std::find_if(cargos.begin(), cargos.end(),
        [&id](const std::unique_ptr<Cargo>& cargo) {
            return cargo->getID() == id;
        });

    if (it != cargos.end())
    {
        (*it)->edit(*dynamic_cast<const Cargo*>(&params));
        return true;
    }

    std::cerr << "Cargo with ID " << id << " not found." << std::endl;
    return false; // Cargo not found
}

bool CargoManager::removeCargo(const std::string& id)
{
    auto it = std::find_if(cargos.begin(), cargos.end(),
        [&id](const std::unique_ptr<Cargo>& cargo) {
            return cargo->getID() == id;
        });

    if (it != cargos.end())
    {
        cargos.erase(it); // Erase the unique_ptr from the vector
        return true;
    }

    std::cerr << "Cargo with ID " << id << " not found." << std::endl;
    return false; // Cargo not found
}

std::vector<Cargo*> CargoManager::getAllCargos() const
{
    std::vector<Cargo*> result;
    for (const auto& cargo : cargos)
    {
        result.push_back(cargo.get()); // Get the raw pointer from unique_ptr
    }
    return result;
}
