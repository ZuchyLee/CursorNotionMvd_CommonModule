#pragma once
#include "Common.hpp"
#include <string>

namespace Automotive {

class ICar {
public:
    virtual ~ICar() = default;

    // 控制命令
    virtual void setPower(bool on) = 0;
    virtual void setThrottle(float position) = 0; // 0.0 ~ 1.0
    virtual void setBrake(float force) = 0;      // 0.0 ~ 1.0
    virtual void setSteering(float angle) = 0;   // -1.0 ~ 1.0 (左至右)

    // 狀態讀取
    virtual VehicleState getState() const = 0;
    virtual std::string getModelName() const = 0;
};

} // namespace Automotive

