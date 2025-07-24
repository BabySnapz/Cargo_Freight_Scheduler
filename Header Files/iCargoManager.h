#pragma once
#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Cargo.h"
#include "CargoParams.h"

class iCargoManager 
{
public:
	virtual ~iCargoManager() = default;
	virtual bool loadFromFile(const std::string& filepath) = 0;
	virtual bool addCargo(std::unique_ptr<Cargo> cargo) = 0;
	virtual bool createCargo(const std::string& id, const std::string& location,
		const std::string& time, int cargoGrouping) = 0;
	virtual bool editCargo(const std::string& id,
		const iRecordParams& params) = 0;
	virtual bool removeCargo(const std::string& id) = 0;
	virtual std::vector<Cargo*> getAllCargos() const = 0;
};



