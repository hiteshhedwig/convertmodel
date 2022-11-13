project(ConvertModel)
cmake_minimum_required(VERSION 3.15) # for CMAKE_CXX_STANDARD

set (
    NCNN_HEADER
    /usr/local/include/ncnn
)

set (
    NCNN_LAYERS
    ncnn_src/
)


set (
    NCNN_LIBS
    /usr/local/lib/ncnn/libncnn.a  /usr/local/lib/ncnn/libglslang.a /usr/local/lib/ncnn/libSPIRV.a /usr/local/lib/ncnn/libMachineIndependent.a /usr/local/lib/ncnn/libOGLCompiler.a /usr/local/lib/ncnn/libOSDependent.a /usr/local/lib/ncnn/libGenericCodeGen.a
)

set (
    VULKAN_LIBS  
    /usr/lib/x86_64-linux-gnu/libvulkan.so 
)

set (
    CPP_LIBS
     -lpthread -pthread -lgomp 
)

set (
    CFLAGS
    -pthread 
)

add_executable(ncnnoptimize ncnnoptimize.cpp)
target_compile_features(ncnnoptimize PRIVATE cxx_std_17)

target_include_directories(ncnnoptimize PUBLIC "${NCNN_HEADER}")
target_include_directories(ncnnoptimize PUBLIC "${NCNN_LAYERS}")
target_link_libraries(ncnnoptimize PUBLIC "${NCNN_LIBS}")
target_link_libraries(ncnnoptimize PUBLIC "${CFLAGS}")
target_link_libraries(ncnnoptimize PUBLIC "${CPP_LIBS}")
target_link_libraries(ncnnoptimize PUBLIC "${VULKAN_LIBS}")