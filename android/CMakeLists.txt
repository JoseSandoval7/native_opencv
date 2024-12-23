cmake_minimum_required(VERSION 3.4.1)

include_directories(../include)
add_library(lib_opencv SHARED IMPORTED)
set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../cmakeLibs/${ANDROID_ABI}/libopencv_java4.so)

set(IMAGE_PROCESSOR_DIR "../ios/Classes")
set(SOURCES
    ${IMAGE_PROCESSOR_DIR}/ImageProcessor.cpp
    ${IMAGE_PROCESSOR_DIR}/native_opencv.cpp
)

add_library(native_opencv SHARED ${SOURCES})
target_link_libraries(native_opencv lib_opencv)