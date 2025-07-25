#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

#include "CargoManager.h"

bool CargoManager::loadFromFile(const std::string& filepath) 
{
    vector<unique_ptr<Cargo>> list;
    try {
        list = fileHandler.loadTyped<Cargo>(filepath, c_Factory);
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to load cargos from ?"
            << filepath << "? " << e.what() << "\n";
        return false;
    }
    for (auto& c : list) {
        if (!addCargo(std::move(c))) {
            std::cerr << "Duplicate cargo ID\n";
            return false;
        }
    }
    return true;
}

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
    // 1) Find the existing Cargo by ID
    auto it = std::find_if(cargos.begin(), cargos.end(),
        [&](const std::unique_ptr<Cargo>& c) 
        {
            return c->getID() == id;
        });

    if (it == cargos.end())
    {
        std::cerr << "Cargo with ID " << id << " not found.\n";
        return false;
    }

    // 2) Use the factory to build a fresh Cargo from params
    std::unique_ptr<iRecord> newRec = c_Factory.create(params);
    auto* newCargo = dynamic_cast<Cargo*>(newRec.get());
    if (!newCargo)
    {
        std::cerr << "Factory did not produce a Cargo instance.\n";
        return false;
    }

    // 3) Delegate all field?copying to Cargo::edit()
    (*it)->edit(*newCargo);
    return true;
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

std::vector<iCargo*> CargoManager::getAllCargos() const
{
    std::vector<iCargo*> result;
    for (const auto& cargo : cargos)
    {
        result.push_back(cargo.get()); // Get the raw pointer from unique_ptr
    }
    return result;
}
