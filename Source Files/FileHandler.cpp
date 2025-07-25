#include <fstream>
#include <iostream>
#include "FileHandler.h"
#include "StringTools.h"
#include "Freight.h"
#include "Cargo.h"

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

template<typename T>
vector<unique_ptr<T>>
FileHandler::loadTyped(const string& path,
	const iRecordFactory& factory) const
{
	auto base = load(path, factory);
	vector<unique_ptr<T>> out;
	for (auto& rec : base) {
		// make sure it really is a T
		if (auto* ptr = dynamic_cast<T*>(rec.get())) {
			// take ownership as T
			out.emplace_back(static_cast<T*>(rec.release()));
		}
		else {
			throw runtime_error("FileHandler::loadTyped<"
				+ string(typeid(T).name())
				+ ">: unexpected record type");
		}
	}
	return out;
}

template std::vector<std::unique_ptr<Freight>>
FileHandler::loadTyped<Freight>(const std::string&, const iRecordFactory&) const;

template std::vector<std::unique_ptr<Cargo>>
FileHandler::loadTyped<Cargo>(const std::string&, const iRecordFactory&) const;