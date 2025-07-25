#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

#include "FreightManager.h"

bool FreightManager::loadFromFile(const string& filepath) {
    // 1) parse+build+type-filter all in one go
    vector<unique_ptr<Freight>> list;
    try {
        list = aFileHandler.loadTyped<Freight>(filepath, f_Factory);
    }
    catch (const exception& e) {
        cerr << "Failed to load freights from ?"
            << filepath << "? " << e.what() << "\n";
        return false;
    }

    // 2) store them
    for (auto& f : list) {
        if (!addFreight(move(f))) {
            cerr << "Duplicate freight ID\n";
            return false;
        }
    }
    return true;
}

bool FreightManager::addFreight(std::unique_ptr<Freight> freight)
{
    freights.push_back(std::move(freight));
    return true;
}

bool FreightManager::createFreight(const std::string& id, const std::string& location,
    const std::string& time, const FreightType& freightType)
{
    auto freightParams = std::make_unique<FreightParams>();
    freightParams->setID(id)
        .setLocation(location)
        .setTime(time)
        .setFreightType(freightType);

    auto freight = std::unique_ptr<Freight>(static_cast<Freight*>(f_Factory.create(*freightParams).release()));

    return addFreight(std::move(freight));
}

bool FreightManager::editFreight(const std::string& id,
    const iRecordParams& params)
{
    // 1) Locate the freight
    auto it = std::find_if(freights.begin(), freights.end(),
        [&](const std::unique_ptr<Freight>& f) 
        {
            return f->getID() == id;
        });

    if (it == freights.end()) 
    {
        std::cerr << "Freight with ID " << id << " not found.\n";
        return false;
    }

    // 2) Use the factory to build a brand?new Freight from params
    std::unique_ptr<iRecord> newRec = f_Factory.create(params);
    auto* newFreight = dynamic_cast<Freight*>(newRec.get());
    if (!newFreight) 
    {
        std::cerr << "Factory did not produce a Freight instance.\n";
        return false;
    }

    // 3) Delegate all field?copying logic to Freight::edit()
    (*it)->edit(*newFreight);
    return true;
}

bool FreightManager::removeFreight(const std::string& id)
{
    auto it = std::find_if(freights.begin(), freights.end(),
        [&id](const std::unique_ptr<Freight>& freight) {
            return freight->getID() == id;
        });

    if (it != freights.end())
    {
        freights.erase(it);
        return true;
    }

    std::cerr << "Freight with ID " << id << " not found." << std::endl;
    return false;
}

std::vector<iFreight*> FreightManager::getAllFreights() const
{
    std::vector<iFreight*> result;
    for (const auto& freight : freights)
    {
        result.push_back(freight.get()); 
    }
    return result;
}

