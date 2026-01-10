#pragma once

namespace Automotive {

class IEngine {
public:
    virtual ~IEngine() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
    virtual float getOutputTorque() const = 0; // 輸出扭矩
};

} // namespace Automotive

