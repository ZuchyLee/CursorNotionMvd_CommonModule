cmake_minimum_required(VERSION 3.10)
project(LibAutomotive)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含路徑
include_directories(include)

# 函式庫實作
add_library(AutomotiveCore STATIC 
    src/VehicleFactory.cpp
)

# 範例執行檔
add_executable(AutomotiveExample examples/main.cpp)
target_link_libraries(AutomotiveExample AutomotiveCore)

