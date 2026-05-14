cmake_minimum_required(VERSION 3.16)

project(WSLCPPContainer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#add_executable(app src/helloworld/main.cpp)
# add_executable(app src/singleton/main.cpp)
# add_executable(app src/factory/main.cpp)
# add_executable(app src/observer/main.cpp)
# add_subdirectory(src/singleton)


message(STATUS
    "Available patterns:
     singleton
     observer
     builder
     factory")

set(PATTERN "" CACHE STRING "Design pattern")

if(PATTERN STREQUAL "singleton")
add_executable(singleton
        src/singleton/main.cpp)

elseif(PATTERN STREQUAL "observer")

    add_executable(observer
        src/observer/main.cpp)

elseif(PATTERN STREQUAL "builder")

    add_executable(builder
        builder/main.cpp)

elseif(PATTERN STREQUAL "factory")

    add_executable(factory
        src/factory/main.cpp)

else()

    message(FATAL_ERROR
        "Unknown PATTERN. Use:
        -DPATTERN=singleton
        -DPATTERN=observer
        -DPATTERN=builder
        -DPATTERN=factory")

endif()