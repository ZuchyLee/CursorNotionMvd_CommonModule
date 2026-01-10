#include "Automotive/IEngine.hpp"
#include <iostream>

namespace Automotive {

class ElectricEngine : public IEngine {
public:
    ElectricEngine() : m_running(false) {}

    void start() override {
        m_running = true;
        std::cout << "[ElectricEngine] Motor started." << std::endl;
    }

    void stop() override {
        m_running = false;
        std::cout << "[ElectricEngine] Motor stopped." << std::endl;
    }

    bool isRunning() const override {
        return m_running;
    }

    float getOutputTorque() const override {
        return m_running ? 350.0f : 0.0f; // 假設固定扭矩
    }

private:
    bool m_running;
};

} // namespace Automotive

