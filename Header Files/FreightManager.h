#pragma once
#include <string>
#include <vector>
#include "iFreightManager.h"
#include "FreightFactory.h"

class FreightManager : public iFreightManager
{
private:
	std::vector<std::unique_ptr<Freight>> freights;
	FreightFactory f_Factory;

public: 	
	~FreightManager() override = default;
	bool loadFromFile(const std::string& filepath) override;
	bool addFreight(std::unique_ptr<Freight> freight);
	bool createFreight(const std::string& id, const std::string& location,
		const std::string& time, const FreightType& freightType);
	bool editFreight(const std::string& id,
		const FreightParams& params);
	bool removeFreight(const std::string& id);
	std::vector<Freight*> getAllFreights() const override;
};
