cmake_minimum_required(VERSION 3.10)
project(strata-solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        strata_solver
        src/main.cpp
        src/Solver.cpp
        src/Map.cpp
        src/Solution.cpp
        src/Color.cpp
        src/Move.cpp
        src/ColorChecker.cpp
)
target_include_directories(strata_solver PRIVATE include)
