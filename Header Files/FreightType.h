#pragma once
#include <string>
#include <string_view>
#include <stdexcept>

enum class FreightType { MiniMover, CargoCruiser, MegaCarrier };

inline constexpr const char* freightTypeToString(FreightType t) {
	switch (t)
	{
	case FreightType::MiniMover:
		return "MiniMover";
	case FreightType::CargoCruiser:
		return "CargoCruiser";
	case FreightType::MegaCarrier:
		return "MegaCarrier";
	}
	return "Unknown";
}

inline const FreightType stringToFreightType(const std::string_view aString) {
	if (aString == "MiniMover")
		return FreightType::MiniMover;
	else if (aString == "CargoCruiser")
		return FreightType::CargoCruiser;
	else if (aString == "MegaCarrier")
		return FreightType::MegaCarrier;
	throw std::invalid_argument("Unknown FreighType: " + std::string(aString));
}

inline int computeCapacity(FreightType t) {
	switch (t)
	{
	case FreightType::MiniMover:
		return 2;
	case FreightType::CargoCruiser:
		return 6;
	case FreightType::MegaCarrier:
		return 12;
	}
	return 0;
}