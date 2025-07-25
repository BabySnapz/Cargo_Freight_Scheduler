#pragma once
#include <string>
#include <vector>
#include "iFreightManager.h"
#include "iRecordFactory.h"
#include "FileHandler.h"

class FreightManager : public iFreightManager
{
private:
	std::vector<std::unique_ptr<Freight>> freights;
	FileHandler& aFileHandler;
	iRecordFactory& f_Factory;
	
public:
	~FreightManager() override = default;

	FreightManager(FileHandler& aFileHandler_, iRecordFactory& aFactory)
		: aFileHandler(aFileHandler_), f_Factory(aFactory) 
	{
		
	}

	bool loadFromFile(const std::string& filepath) override;

	bool addFreight(std::unique_ptr<Freight> freight) override;

	bool createFreight(const std::string& id, const std::string& location,
		const std::string& time, const FreightType& freightType) override;

	bool editFreight(const std::string& id, const iRecordParams& params) override;

	bool removeFreight(const std::string& id) override;

	std::vector<iFreight*> getAllFreights() const override;
};