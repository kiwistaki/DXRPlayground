cmake_minimum_required (VERSION 3.14.1)

project ("DXR_Playground")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT DXR)

