cmake_minimum_required(VERSION 3.20)

project(Lab1_GroupProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Lab1App
    main.cpp
    student_a.cpp
    student_b.cpp
)

target_compile_features(Lab1App PRIVATE cxx_std_20)