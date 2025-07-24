#include <fstream>
#include <iostream>
#include "FileHandler.h"
#include "StringTools.h"

using namespace std;
using namespace StringTools;

vector<unique_ptr<iRecord>> FileHandler::load(const string& filePath, 
	const iRecordFactory& factory) const {
	ifstream in(filePath);

	if (!in) throw std::runtime_error("Cannot open " + filePath);

	vector<unique_ptr<iRecord>> newRecord;
	string line;

	while (getline(in, line)) {
		if (line.empty())
			continue;

		auto tokens = split(line, ',');

		auto params = factory.makeEmptyParams();
		try
		{
			params->fieldsFromFile(tokens);		
		}
		catch (const std::exception& e)
		{
			cerr << "Skipping malformed row: " << e.what() << endl;
			continue;
		}
		auto record = factory.create(*params);
		newRecord.emplace_back(move(record));
	}
	return newRecord;
}