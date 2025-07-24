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

std::vector<std::string> CargoManager::tokenize(const std::string& str)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, ','))  // CSV format: comma-separated values
    {
        tokens.push_back(token);
    }

    return tokens;
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

bool CargoManager::loadFromFile(const std::string& filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = tokenize(line);

        try
        {
            auto cargoParams = std::make_unique<CargoParams>();
            cargoParams->fieldsFromFile(tokens);

            auto cargo = std::unique_ptr<Cargo>(static_cast<Cargo*>(c_Factory.create(*cargoParams).release()));
            addCargo(std::move(cargo));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading cargo from file: " << e.what() << std::endl;
            continue;
        }
    }

    return true;
}