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

	bool addCargo(std::unique_ptr<Cargo> cargo) override;

	bool createCargo(const std::string& id, const std::string& location,
		const std::string& time, int cargoGrouping) override;

	bool editCargo(const std::string& id,
		const iRecordParams& params) override;

	bool removeCargo(const std::string& id) override;

	std::vector<Cargo*> getAllCargos() const override;
	std::vector<std::string> tokenize(const std::string& str);
};
