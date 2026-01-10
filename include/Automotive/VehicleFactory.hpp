#pragma once
#include "ICar.hpp"
#include <memory>

namespace Automotive {

class VehicleFactory {
public:
    enum class CarType {
        Sedan_EV,    // 電動轎車
        SUV_Gasoline // 燃油SUV
    };

    static std::unique_ptr<ICar> createVehicle(CarType type);
};

} // namespace Automotive

