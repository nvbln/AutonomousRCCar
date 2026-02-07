cmake_minimum_required(VERSION 3.15...4.2)

project(AutonomousRCCar VERSION 0.1
                        DESCRIPTION "Autonomous RC Car program"
                        LANGUAGES CXX)

# Allows LSPs to read out compilation settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKe_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(interfaces INTERFACE)
target_include_directories(interfaces INTERFACE src/interfaces)

add_library(hal INTERFACE)
target_include_directories(hal INTERFACE src/hal)

add_library(core STATIC
    src/core/Core.cpp
    src/core/LedController.cpp
)

target_include_directories(core PUBLIC src/core)
target_link_libraries(core PUBLIC interfaces)
target_link_libraries(core PUBLIC hal)

enable_testing()

add_executable(core_test
    test/LedControllerTest.cpp
)

target_link_libraries(core_test
    PRIVATE core interfaces hal
    PUBLIC GTest::gtest_main GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(core_test)
