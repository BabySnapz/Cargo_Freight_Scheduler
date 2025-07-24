#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Freight.h"
#include "FreightParams.h"
#include "FreightType.h"

class iFreightManager 
{
public:
	virtual ~iFreightManager() = default;
	virtual bool loadFromFile(const std::string& filepath) = 0;
	virtual bool addFreight(std::unique_ptr<Freight> freight) = 0;
	virtual bool createFreight(const std::string& id, const std::string& location,
		const std::string& time, FreightType freightType) = 0;
	virtual bool editFreight(const std::string& id,
	const iRecordParams& params) = 0;
	virtual bool removeFreight(const std::string& id) = 0;
	virtual std::vector<Freight*> getAllFreights() const = 0;
};