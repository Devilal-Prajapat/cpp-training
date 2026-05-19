cmake_minimum_required(VERSION 3.16)

project(WSLCPPContainer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS
    "Available principles:
     SRP
     OCP
     LSP
     ISP
     DIP")

set(PRINCIPLE "" CACHE STRING "SOLID principle")

if(PRINCIPLE STREQUAL "SRP")
    add_executable(app single_responsibility.cpp)
elseif(PRINCIPLE STREQUAL "OCP")
    add_executable(app open_close.cpp)
elseif(PRINCIPLE STREQUAL "LSP")
    add_executable(app liskov_substitution.cpp)     
elseif(PRINCIPLE STREQUAL "ISP")
    add_executable(app interface_segregation.cpp)
elseif(PRINCIPLE STREQUAL "DIP")
    add_executable(app dependency_inversion.cpp)
else()
    message(FATAL_ERROR
        "Unknown PRINCIPLE. Use:
        -DPRINCIPLE=SRP
        -DPRINCIPLE=OCP
        -DPRINCIPLE=LSP         
        -DPRINCIPLE=ISP
        -DPRINCIPLE=DIP")
endif()


# cmake -B build -DPRINCIPLE=SRP && cmake --build build