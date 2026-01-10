## CursorNotionMvd_CommonModule

這是一個以「汽車」為例的 C++ 共用模組示範（`LibAutomotive`）。

### 內容
- `include/Automotive/`：公開介面（供其他專案引用）
- `src/`：內部實作
- `examples/`：最小可執行範例
- `AutomotiveModule_Design.md`：設計概念與介面文件
- `AutomotiveModule_Review_Guidelines.md`：給 AI/人員做 Code Review 的規範

### Build / Run（CMake）

```bash
cmake -S . -B build
cmake --build build

# Windows PowerShell
.\build\AutomotiveExample.exe
```

> 若你使用 MSYS2/MinGW 的 GCC，請確保把 `C:\msys64\ucrt64\bin` 加到 PATH，否則執行時可能缺 DLL。
