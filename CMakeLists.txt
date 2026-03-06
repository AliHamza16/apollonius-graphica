cmake_minimum_required(VERSION 3.15)
project(ApolloniusGraphica VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/External/SFML/include")
set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/External/SFML/lib")

file(GLOB_RECURSE CORE_SOURCES "Core/*.cpp")

add_executable(ApolloniusGraphica "App/App.cpp" ${CORE_SOURCES})

target_include_directories(ApolloniusGraphica PRIVATE 
    "${CMAKE_SOURCE_DIR}/Core"
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(ApolloniusGraphica PRIVATE
    "${SFML_LIB_DIR}/libsfml-graphics.so"
    "${SFML_LIB_DIR}/libsfml-window.so"
    "${SFML_LIB_DIR}/libsfml-system.so"
)

set_target_properties(ApolloniusGraphica PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${SFML_LIB_DIR}"
)
