#include "SchedulerManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void SchedulerManager::setStrategy(SortAlgorithms* strategy)
{
    this->sortStrategy = strategy;


}

void SchedulerManager::exportSchedule(const std::string& filepath)
{
    fs::path inputPath(filepath);
    fs::path filePath;

    if (inputPath.has_filename() && inputPath.extension() == ".txt")
    {
        filePath = inputPath;
    }
    else
    {
        if (!fs::exists(inputPath)) {
            try
            {
                fs::create_directories(inputPath);
            }
            catch (const fs::filesystem_error& e)
            {
                cerr << "Failed to create directory: " << e.what() << endl;
                return;
            }
        }
        filePath = inputPath / "Schedule.txt";
    }

    // Export logic would go here (if needed)
}

std::vector<std::pair<const iFreight&, const iCargo&>> SchedulerManager::getMatchedList()
{
    return matchedList;
}

std::vector<std::pair<const iFreight&, const iCargo&>> SchedulerManager::createMatchedList(
    const std::vector<const iFreight*>& freights,
    const std::vector<const iCargo*>& cargos)
{
    if (!sortStrategy) {
        std::cout << "[DEBUG] Sort strategy not set!\n";
        return {};
    }

    matchedList = sortStrategy->sortList(freights, cargos);
    return matchedList;
}




//void SchedulerManager::exportSchedule(const std::string& filepath)
//{
//    fs::path inputPath(filepath);
//
//    fs::path filePath;
//
//    // If the user included a filename (e.g., ends with .txt), use it directly
//    if (inputPath.has_filename() && inputPath.extension() == ".txt")
//    {
//        filePath = inputPath;
//    }
//    else
//    {
//        // Otherwise, treat it as a folder and append Schedule.txt
//        if (!fs::exists(inputPath)) {
//            try
//            {
//                fs::create_directories(inputPath);
//            }
//            catch (const fs::filesystem_error& e)
//            {
//                cerr << "Failed to create directory: " << e.what() << endl;
//                return;
//            }
//        }
//        filePath = inputPath / "Schedule.txt";
//    }
//
//    //ofstream outFile(filePath);
//
//    /*if (!outFile.is_open())  //printing the details of the exporting document
//    {
//        cerr << "Error: Unable to open file for writing: " << filepath << endl;
//        return;
//    }
//
//    outFile << "--- Matched Freight and Cargo Records ---\n";
//    outFile << left
//        << setw(8) << "F_ID"
//        << setw(12) << "F_Location"
//        << setw(8) << "F_Time"
//        << " | "
//        << setw(8) << "C_ID"
//        << setw(12) << "C_Location"
//        << setw(8) << "C_Time"
//        << "\n";
//    outFile << string(65, '-') << "\n";
//
//    for (const auto& pair : matchedList) {
//        Freight* f = pair.first;
//        Cargo* c = pair.second;
//
//        outFile << left
//            << setw(8) << f->getID()
//            << setw(12) << f->getLocation()
//            << setw(8) << f->getTime()
//            << " | "
//            << setw(8) << c->getID()
//            << setw(12) << c->getLocation()
//            << setw(8) << c->getTime()
//            << "\n";
//    }
//
//    outFile << "\n--- Unmatched Freight Records ---\n";
//    outFile << left
//        << setw(8) << "F_ID"
//        << setw(12) << "F_Location"
//        << setw(8) << "F_Time"
//        << "\n";
//    outFile << string(30, '-') << "\n";
//
//    for (Freight* f : unmatchedFreights) {
//        outFile << left
//            << setw(8) << f->getID()
//            << setw(12) << f->getLocation()
//            << setw(8) << f->getTime()
//            << "\n";
//    }
//
//    outFile << "\n--- Unmatched Cargo Records ---\n";
//    outFile << left
//        << setw(8) << "C_ID"
//        << setw(12) << "C_Location"
//        << setw(8) << "C_Time"
//        << "\n";
//    outFile << string(30, '-') << "\n";
//
//    for (Cargo* c : unmatchedCargos) {
//        outFile << left
//            << setw(8) << c->getID()
//            << setw(12) << c->getLocation()
//            << setw(8) << c->getTime()
//            << "\n";
//    }
//
//    outFile.close();*/
//    //cout << "Exporting schedule to " << filepath << endl;
//}