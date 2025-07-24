#include "CargoFactory.h"
#include "Cargo.h"

using namespace std;

unique_ptr<iRecordParams> CargoFactory::makeEmptyParams() const {
	return make_unique<CargoParams>();
}

unique_ptr<iRecord> CargoFactory::create(const iRecordParams& params) const {
	auto const& params_ = dynamic_cast<const CargoParams&>(params);

	const auto& id = params_.getID();
	const auto& location = params_.getLocation();
	const auto& time = params_.getTime();
	const auto& cargoGrouping = params_.getCargoGrouping();

	return make_unique<Cargo>(id, location, time, cargoGrouping);
}
