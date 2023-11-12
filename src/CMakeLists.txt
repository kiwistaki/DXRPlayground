file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB HEADER_FILES_SUB "${CMAKE_CURRENT_SOURCE_DIR}/nv_helpers_dx12/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB SOURCE_FILES_SUB "${CMAKE_CURRENT_SOURCE_DIR}/nv_helpers_dx12/*.cpp")

add_executable(DXR WIN32 ${HEADER_FILES} ${HEADER_FILES_SUB}
                         ${SOURCE_FILES} ${SOURCE_FILES_SUB}
    )
              
set_property(TARGET DXR PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:DXR>)
target_include_directories(DXR PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

source_group("Header Files\\nv_helpers_dx12" FILES ${HEADER_FILES_SUB})
source_group("Source Files\\nv_helpers_dx12" FILES ${SOURCE_FILES_SUB})

target_link_libraries(DXR d3d12 dxcompiler dxgi d3dcompiler)
#target_link_libraries(DXR tinyobjloader imgui stb_image)

add_custom_command(TARGET DXR POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/../Shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/Shaders
)