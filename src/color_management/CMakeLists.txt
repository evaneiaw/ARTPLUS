# src/color_management/CMakeLists.txt
add_library(ColorManagement STATIC
    color_manipulation_layer.cpp
    color_manipulation_layer.h
    color_manipulation.cpp
    color_manipulation.h
    callback_converter.cpp
    callback_converter.h
    icc_profile_cache.cpp
    icc_profile_cache.h
    color_lib_info.cpp
    color_lib_info.h
    icc_profile.cpp
    icc_profile.h
)

target_link_libraries(ColorManagement PUBLIC Qt6::Core)
target_include_directories(ColorManagement PUBLIC ${CMAKE_SOURCE_DIR}/src)