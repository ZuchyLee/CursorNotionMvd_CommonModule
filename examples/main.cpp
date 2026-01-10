#include <Automotive/VehicleFactory.hpp>
#include <iostream>
#include <iomanip>

int main() {
    std::cout << "--- Automotive Module Example ---" << std::endl;

    // 1. 建立車輛
    auto myCar = Automotive::VehicleFactory::createVehicle(
        Automotive::VehicleFactory::CarType::Sedan_EV
    );

    if (!myCar) {
        std::cerr << "Failed to create vehicle!" << std::endl;
        return -1;
    }

    std::cout << "Vehicle Model: " << myCar->getModelName() << std::endl;

    // 2. 操作
    myCar->setPower(true);
    myCar->setThrottle(0.6f);
    myCar->setSteering(-0.2f);

    // 3. 顯示狀態
    auto status = myCar->getState();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n[Real-time Status]" << std::endl;
    std::cout << "Speed: " << status.speed << " km/h" << std::endl;
    std::cout << "RPM: " << status.rpm << std::endl;
    std::cout << "Fuel/Battery: " << status.fuelLevel * 100 << "%" << std::endl;

    // 4. 停止
    myCar->setThrottle(0.0f);
    myCar->setBrake(1.0f);
    myCar->setPower(false);

    return 0;
}

