# LibAutomotive（CommonModule）使用說明

本文件是給「**在其他專案引用本共用模組**」時使用的整合指南；設計細節請參考 `AutomotiveModule_Design.md`。

- **規範唯一來源（Notion）**：`https://www.notion.so/MVD-2e43f18e160780f7a2a5ff06887b583a?source=copy_link`
- **Code Review 規範**：`AutomotiveModule_Review_Guidelines.md`

---

## 1. 你會拿到什麼

- **公開介面（外部專案只能 include 這裡）**：`include/Automotive/`
- **連結目標（CMake target）**：`AutomotiveCore`（static library）

---

## 2. 整合方式（推薦：add_subdirectory）

在你的專案中把本 repo 放進來（例如 Git submodule 或直接複製資料夾），假設路徑為：

```text
YourProject/
└── third_party/
    └── CommonModule/   (本 repo)
```

然後在你的 `CMakeLists.txt`：

```cmake
add_subdirectory(third_party/CommonModule)

add_executable(YourApp src/main.cpp)
target_link_libraries(YourApp PRIVATE AutomotiveCore)
```

> 備註：本模組目前用 `include_directories(include)` 做包含路徑設定；因此只要 link 到 `AutomotiveCore`，即可使用 `#include <Automotive/...>`。

---

## 3. 最小使用範例

外部專案程式碼（等同 `examples/main.cpp` 的精簡版）：

```cpp
#include <Automotive/VehicleFactory.hpp>
#include <iostream>

int main() {
    auto car = Automotive::VehicleFactory::createVehicle(
        Automotive::VehicleFactory::CarType::Sedan_EV
    );
    if (!car) return 1;

    car->setPower(true);
    car->setThrottle(0.6f);
    car->setSteering(-0.2f);

    auto state = car->getState();
    std::cout << "Model=" << car->getModelName()
              << " speed=" << state.speed
              << " rpm=" << state.rpm
              << std::endl;

    car->setBrake(1.0f);
    car->setPower(false);
    return 0;
}
```

---

## 4. 使用規範（外部專案必遵守）

### 4.1 只能引用公開標頭檔

- **允許**：`#include <Automotive/ICar.hpp>`、`#include <Automotive/VehicleFactory.hpp>` 等 `include/Automotive/` 之下的檔案
- **禁止**：引用 `src/` 底下任何檔案（包含 `.hpp/.cpp`）

### 4.2 一律透過工廠建立物件（禁止 new 實作類）

- **正確**：`Automotive::VehicleFactory::createVehicle(...)`
- **禁止**：直接 `new`/`make_unique` 任何實作類別（例如 `CarImpl`、`ElectricEngine`）

### 4.3 介面參數範圍

- `setThrottle(position)`: 0.0 ~ 1.0
- `setBrake(force)`: 0.0 ~ 1.0
- `setSteering(angle)`: -1.0 ~ 1.0

### 4.4 不要改動共用模組本身

若你是在「使用」這個模組的專案（不是在維護模組），PR 不應修改：

- `CommonModule/include/`
- `CommonModule/src/`

---

## 5. 常見問題

### 5.1 我該看設計文件還是使用說明？

- **要整合、要寫業務邏輯**：看本檔 `USAGE.md` + `AutomotiveModule_Review_Guidelines.md`
- **要擴充車型/修改模組行為**：看 `AutomotiveModule_Design.md`

