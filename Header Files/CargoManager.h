#pragma once
#include "iCargoManager.h"
#include "iRecordFactory.h"
#include "FileHandler.h"

class CargoManager : public iCargoManager
{
private:
	std::vector<std::unique_ptr<Cargo>> cargos;
	FileHandler& fileHandler;
	iRecordFactory& c_Factory;
public:
	~CargoManager() override = default;

	CargoManager(FileHandler& fileHandler_, iRecordFactory& factory_) 
		: fileHandler(fileHandler_), c_Factory(factory_)
	{
	
	}

	bool loadFromFile(const std::string& filepath) override;

	bool addCargo(std::unique_ptr<Cargo> cargo) override;

	bool createCargo(const std::string& id, const std::string& location,
		const std::string& time, int cargoGrouping) override;

	bool editCargo(const std::string& id,
		const iRecordParams& params) override;

	bool removeCargo(const std::string& id) override;

	std::vector<Cargo*> getAllCargos() const override;
};
