#include "Automotive/ICar.hpp"
#include "Automotive/IEngine.hpp"
#include <iostream>
#include <memory>

namespace Automotive {

class CarImpl : public ICar {
public:
    CarImpl(std::string model, std::unique_ptr<IEngine> engine)
        : m_model(std::move(model)), m_engine(std::move(engine)), m_powerOn(false),
          m_throttle(0.0f), m_brake(0.0f), m_steering(0.0f) {}

    void setPower(bool on) override {
        m_powerOn = on;
        if (on) {
            m_engine->start();
        } else {
            m_engine->stop();
        }
        std::cout << "[CarImpl] Power " << (on ? "ON" : "OFF") << std::endl;
    }

    void setThrottle(float position) override {
        if (!m_powerOn) return;
        m_throttle = position;
        std::cout << "[CarImpl] Throttle set to " << position * 100 << "%" << std::endl;
    }

    void setBrake(float force) override {
        m_brake = force;
        std::cout << "[CarImpl] Brake set to " << force * 100 << "%" << std::endl;
    }

    void setSteering(float angle) override {
        m_steering = angle;
        std::cout << "[CarImpl] Steering angle set to " << angle << std::endl;
    }

    VehicleState getState() const override {
        VehicleState state;
        state.speed = m_throttle * 180.0f; // 簡易模擬
        state.rpm = m_engine->isRunning() ? (m_throttle * 8000.0f) : 0.0f;
        state.fuelLevel = 0.85f; // 假數據
        state.currentGear = Gear::D;
        return state;
    }

    std::string getModelName() const override {
        return m_model;
    }

private:
    std::string m_model;
    std::unique_ptr<IEngine> m_engine;
    bool m_powerOn;
    float m_throttle;
    float m_brake;
    float m_steering;
};

} // namespace Automotive

