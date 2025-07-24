#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#include "FreightManager.h"

//Records* FreightManager::makeRecord(const string& id, const string& destination, const string& arrivalTime) 
//{
//	return new Freight(id, destination, arrivalTime);
//}
//
//bool FreightManager::addFreight(Freight* freight)
//{
//  return addRecordToVector(freight);
//}

std::vector<std::string> FreightManager::tokenize(const std::string& str)
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

bool FreightManager::loadFromFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = tokenize(line);

        try
        {
            auto freightParams = std::make_unique<FreightParams>();
            freightParams->fieldsFromFile(tokens);

            auto freight = std::unique_ptr<Freight>(static_cast<Freight*>(f_Factory.create(*freightParams).release()));

            addFreight(std::move(freight));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading freight from file: " << e.what() << std::endl;
            continue; // Skip invalid lines
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

bool FreightManager::editFreight(const std::string& id, const iRecordParams& params)
{
    // Find the Freight by ID
    auto it = std::find_if(freights.begin(), freights.end(),
        [&id](const std::unique_ptr<Freight>& freight) {
            return freight->getID() == id;
        });

    if (it != freights.end())
    {
        // Cast the iRecordParams to FreightParams
        const FreightParams& freightParams = dynamic_cast<const FreightParams&>(params);

        // Call edit with the correct params
        (*it)->edit(*dynamic_cast<const Freight*>(&params));
        return true;
    }

    std::cerr << "Freight with ID " << id << " not found." << std::endl;
    return false;
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

std::vector<Freight*> FreightManager::getAllFreights() const
{
    std::vector<Freight*> result;
    for (const auto& freight : freights)
    {
        result.push_back(freight.get()); // Get the raw pointer
    }
    return result;
}