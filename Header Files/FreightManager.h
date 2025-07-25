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

	bool addFreight(std::unique_ptr<Freight> freight) override;

	bool createFreight(const std::string& id, const std::string& location,
		const std::string& time, const FreightType& freightType) override;

	bool editFreight(const std::string& id, const iRecordParams& params) override;

	bool removeFreight(const std::string& id) override;

	std::vector<Freight*> getAllFreights() const override;
};