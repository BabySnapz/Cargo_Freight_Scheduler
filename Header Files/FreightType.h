#pragma once
#include <string>
enum class FreightType { MiniMover, CargoCruiser, MegaCarrier };

inline constexpr const char* freightTypeToString(FreightType t){
	switch (t)
	{
	case FreightType::MiniMover:
		return "MiniMover";
	case FreightType::CargoCruiser:
		return "CargoCruiser";
	case FreightType::MegaCarrier:
		return "MegaCarrier";
	default:
		"Unknown freight type";
	}
}