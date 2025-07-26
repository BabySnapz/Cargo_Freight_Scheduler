#include <fstream>
#include <iostream>
#include <filesystem>
#include "FileHandler.h"
#include "StringTools.h"
#include "Freight.h"
#include "Cargo.h"

using namespace std;
using namespace StringTools;
namespace fs = std::filesystem;

vector<unique_ptr<iRecord>> FileHandler::load(const string& filePath, 
	const iRecordFactory& factory) const {

	string copyFilePath = filePath;

	if (!copyFilePath.empty() && copyFilePath.front() == '"' && copyFilePath.back() == '"') {
		copyFilePath = copyFilePath.substr(1, copyFilePath.length() - 2);
	}

	ifstream in(copyFilePath);

	if (!in) throw std::runtime_error("Cannot open " + filePath);

	vector<unique_ptr<iRecord>> newRecord;
	string line;

	while (getline(in, line)) {
		if (line.empty())
			continue;

		// in FileHandler::load, right before split(line, ','):
		while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) {
			line.pop_back();
		}

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

void FileHandler::exportSchedule(const std::string& filepath,
	const std::vector<std::tuple<const iFreight&, const iCargo&, int, int>>& matchedList) const
{
	// 1. Resolve path
	fs::path p(filepath);
	fs::path out;
	if (p.has_filename() && p.extension() == ".txt") {
		out = p;
	}
	else {
		if (!fs::exists(p)) fs::create_directories(p);
		out = p / "Schedule.txt";
	}

	// 2. Open file
	std::ofstream ofs(out);
	if (!ofs) {
		std::cerr << "Failed to open " << out << "\n";
		return;
	}

	// 3. Write header
	ofs << "=== Freight¨CCargo Schedule ===\n";

	// 4. Write matches
	if (matchedList.empty()) {
		ofs << "No matches found.\n";
	}
	else {
		for (size_t i = 0; i < matchedList.size(); ++i) {
			const auto& [freight, cargo, used, remain] = matchedList[i];
			ofs << "Match " << (i + 1) << ":\n"
				<< "  Freight: " << freight << "\n"
				<< "  Cargo:   " << cargo << "\n"
				<< "  Used:    " << used << "\n"
				<< "  Remain:  " << remain << "\n\n";
		}
	}
	ofs.close();
}

template std::vector<std::unique_ptr<Freight>>
FileHandler::loadTyped<Freight>(const std::string&, const iRecordFactory&) const;

template std::vector<std::unique_ptr<Cargo>>
FileHandler::loadTyped<Cargo>(const std::string&, const iRecordFactory&) const;