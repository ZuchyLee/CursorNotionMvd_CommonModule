# Automotive Core Module (LibAutomotive) 設計概念與介面文件

本文件定義了 `LibAutomotive` 共用模組的架構設計、核心介面與使用規範。該模組旨在為不同專案（如自動駕駛模擬、車輛診斷系統、遠程控制 App）提供標準化的汽車物理與控制模型。

---

## 1. 設計概念 (Design Concept)

### 1.1 核心目標
*   **標準化**：定義統一的 C++ 介面，隱藏不同車型與動力系統的實現細節。
*   **高複用性**：單一模組可同時支援燃油車 (ICEV) 與電動車 (EV) 專案。
*   **低耦合**：採用介面與實現分離 (PIMPL 或 抽象基類) 模式，確保調用方無需重新編譯即可更換底層實現。

### 1.2 設計原則
1.  **介面驅動設計 (Interface-Driven Design)**：所有的外部交互都通過抽象類別進行。
2.  **模組化 (Modularity)**：將車輛拆分為 `PowerTrain` (動力)、`Steering` (轉向)、`Braking` (制動) 子組件。
3.  **現代 C++ 標準**：使用 C++17/20 標準，優先使用智慧指標 (`std::unique_ptr`) 進行資源管理。

---

## 2. 專案目錄結構

```text
CommonModule/
├── include/              # 公開標頭檔 (Interface)
│   └── Automotive/
│       ├── ICar.hpp      # 汽車主介面
│       ├── IEngine.hpp   # 引擎/馬達介面
│       ├── Common.hpp    # 共有常數與枚舉
│       └── VehicleFactory.hpp # 物件工廠
├── src/                  # 內部實現 (Implementation)
│   ├── CarImpl.cpp
│   └── ElectricEngine.cpp
└── examples/             # 使用範例
    └── main.cpp
```

---

## 3. 核心介面定義 (API Reference)

### 3.1 基礎資料結構 (`Common.hpp`)
```cpp
namespace Automotive {
    enum class DriveMode { Eco, Normal, Sport, Offroad };
    enum class Gear { P, R, N, D, S };

    struct VehicleState {
        float speed;      // 單位: km/h
        float rpm;        // 引擎轉速
        float fuelLevel;  // 0.0 - 1.0 (油量或電量)
        Gear currentGear;
    };
}
```

### 3.2 汽車主介面 (`ICar.hpp`)
```cpp
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
```

---

## 4. 使用範例 (Quick Start)

```cpp
#include <Automotive/VehicleFactory.hpp>
#include <iostream>

int main() {
    // 1. 透過工廠建立一個電動轎車實例
    auto myCar = Automotive::VehicleFactory::createVehicle(
        Automotive::VehicleFactory::CarType::Sedan_EV
    );

    // 2. 啟動電源
    myCar->setPower(true);

    // 3. 踩下油門 (50%)
    myCar->setThrottle(0.5f);

    // 4. 獲取車輛即時狀態
    auto status = myCar->getState();
    std::cout << "目前車速: " << status.speed << " km/h" << std::endl;

    return 0;
}
```

---

## 5. 未來擴展計畫
*   **感測器介面**：增加 LiDAR、Camera 等感測器數據的標準輸出介面。
*   **CAN Bus 模擬**：整合底層通訊協議模擬。
*   **跨平台編譯**：支援 Windows (DLL) 與 Linux (SO) 的自動化建置腳本。

