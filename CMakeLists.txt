
cmake_minimum_required(VERSION 3.0)

# Project
project(convertmodelnew)

find_package(wxWidgets 3.1.4 REQUIRED)
include(${wxWidgets_USE_FILE})

set(
    SOURCES test.cpp
            src/ncnnoptimize.cpp
)

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (
    NCNN_HEADER
    /usr/local/include/ncnn
)

set (
    INCLUDE_HEADER
    /home/eulermotors/hedwig/extras/convertmodel/include
)

set (
    NCNN_LIBS
    /usr/local/lib/ncnn/libncnn.a  /usr/local/lib/ncnn/libglslang.a /usr/local/lib/ncnn/libSPIRV.a /usr/local/lib/ncnn/libMachineIndependent.a /usr/local/lib/ncnn/libOGLCompiler.a /usr/local/lib/ncnn/libOSDependent.a /usr/local/lib/ncnn/libGenericCodeGen.a
)

set (
    NCNN_LAYERS
    ncnn_src/
)

set (
    CPP_LIBS
     -lpthread -pthread -lgomp 
)

set (
    CFLAGS
    -pthread 
)

set (
    VULKAN_LIBS  
    /usr/lib/x86_64-linux-gnu/libvulkan.so 
)

# Target
# add_subdirectory(ncnn_src/layer)
# add_subdirectory(ncnn_src/build)
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${NCNN_LIBS} ${CFLAGS} ${CPP_LIBS} ${VULKAN_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Applications")
target_include_directories(${PROJECT_NAME}  PUBLIC "${NCNN_HEADER}" ${INCLUDE_HEADER}  ${NCNN_LAYERS})
