cmake_minimum_required(VERSION 3.15)
project(ApolloniusGraphica VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SFML_DIR "${CMAKE_SOURCE_DIR}/External/SFML/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

file(GLOB_RECURSE CORE_SOURCES "Core/*.cpp")

add_executable(ApolloniusGraphica "App/App.cpp" ${CORE_SOURCES})

target_include_directories(ApolloniusGraphica PRIVATE "${CMAKE_SOURCE_DIR}/Core")

target_link_libraries(ApolloniusGraphica PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

set_target_properties(ApolloniusGraphica PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/External/SFML/lib"
)

