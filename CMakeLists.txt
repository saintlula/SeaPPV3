cmake_minimum_required(VERSION 3.30)
project(SeaPlusPlus)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB SOURCES "src/*.cpp" "main.cpp" "src/RuleManager.cpp" "src/UnknownCreature.cpp" "src/FreshwaterCreature.cpp")
add_executable(SeaPlusPlus ${SOURCES})
