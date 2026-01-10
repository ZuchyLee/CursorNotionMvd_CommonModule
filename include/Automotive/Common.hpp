#pragma once
#include <string>

namespace Automotive {

enum class DriveMode {
    Eco,
    Normal,
    Sport,
    Offroad
};

enum class Gear {
    P, R, N, D, S
};

struct VehicleState {
    float speed;      // 單位: km/h
    float rpm;        // 引擎轉速
    float fuelLevel;  // 0.0 - 1.0 (油量或電量)
    Gear currentGear;
};

} // namespace Automotive

