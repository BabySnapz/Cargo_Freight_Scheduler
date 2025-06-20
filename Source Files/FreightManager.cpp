#include <string>
#include <vector>

using namespace std;

#include "FreightManager.h"

Records* FreightManager::makeRecord(const string& id, const string& destination, const string& arrivalTime) {
	return new Freight(id, destination, arrivalTime);
}

bool FreightManager::addFreight(Freight* freight)
{
  return addRecordToVector(freight);
}

