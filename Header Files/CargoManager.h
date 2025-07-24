#pragma once

#include "iCargoManager.h"
#include "CargoFactory.h"

class CargoManager : public iCargoManager
{
private:
	std::vector<std::unique_ptr<Cargo>> cargos;
	CargoFactory c_Factory;
public:
	~CargoManager() override = default;
	bool loadFromFile(const std::string& filepath) override;
	bool addCargo(std::unique_ptr<Cargo> cargo);
	bool createCargo(const std::string& id, const std::string& location,
		const std::string& time, int cargoGrouping);
	bool editCargo(const std::string& id,
		const iRecordParams& params);
	bool removeCargo(const std::string& id);
	std::vector<Cargo*> getAllCargos() const override;
};
