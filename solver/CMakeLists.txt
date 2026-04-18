cmake_minimum_required(VERSION 4.2)

project(solver
    VERSION 0.0.1
    DESCRIPTION "Load distribution solver engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SOLVER_BUILD_TESTS "Build tests" ON)

add_library(solver-core
    src/solver/Solver.cpp
)

target_include_directories(solver-core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(solver-core
    PUBLIC
        cxx_std_20
)

target_compile_options(solver-core
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

add_executable(solver-cli
    src/cli/main.cpp
)

target_link_libraries(solver-cli
    PRIVATE
        solver-core
)

if(SOLVER_BUILD_TESTS)
    enable_testing()

    add_executable(solver-tests
        tests/Spring1DTest.cpp
    )

    target_link_libraries(solver-tests
        PRIVATE
            solver-core
    )

    add_test(NAME solver-tests COMMAND solver-tests)
endif()