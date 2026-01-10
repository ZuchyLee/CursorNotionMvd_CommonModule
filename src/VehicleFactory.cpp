#include "Automotive/VehicleFactory.hpp"
#include "CarImpl.cpp"      // 簡化實作，直接包含
#include "ElectricEngine.cpp"

namespace Automotive {

std::unique_ptr<ICar> VehicleFactory::createVehicle(CarType type) {
    if (type == CarType::Sedan_EV) {
        auto engine = std::make_unique<ElectricEngine>();
        return std::make_unique<CarImpl>("Model S - EV", std::move(engine));
    }
    return nullptr;
}

} // namespace Automotive

