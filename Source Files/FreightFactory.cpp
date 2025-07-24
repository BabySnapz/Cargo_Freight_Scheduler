#include "FreightFactory.h"
#include "Freight.h"

using namespace std;

unique_ptr<iRecordParams> FreightFactory::makeEmptyParams() const {
	return make_unique<FreightParams>();
}

unique_ptr<iRecord> FreightFactory::create(const iRecordParams& params) const {
	auto const& params_ = dynamic_cast<const FreightParams&>(params);

	const auto& id = params_.getID();
	const auto& location = params_.getLocation();
	const auto& time = params_.getTime();
	const auto& freightType = params_.getFreightType();

	return make_unique<Freight>(id, location, time, freightType);
}
