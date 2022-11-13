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
    INCLUDEDIR
    ./include
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
     -lpthread -pthread -lgomp -lGL -lglut
)

set (
    CFLAGS
    -pthread 
)

set (
    GUI_LIBS
    lib/imgui/
)

set (
    GUI_LIBS_BKD
    lib/imgui/backends
)

add_executable(
    Main main.cpp
    src/ncnnoptimize.cpp
    lib/imgui/imgui.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui_draw.cpp 
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/backends/imgui_impl_glut.cpp
    lib/imgui/backends/imgui_impl_opengl2.cpp

)
target_compile_features(Main PRIVATE cxx_std_17)

target_include_directories(Main PUBLIC "${NCNN_HEADER}")
target_include_directories(Main PUBLIC "${NCNN_LAYERS}")
target_include_directories(Main PUBLIC "${INCLUDEDIR}")
target_include_directories(Main PUBLIC "${GUI_LIBS}")
target_include_directories(Main PUBLIC "${GUI_LIBS_BKD}")


target_link_libraries(Main PUBLIC "${NCNN_LIBS}")
target_link_libraries(Main PUBLIC "${CFLAGS}")
target_link_libraries(Main PUBLIC "${CPP_LIBS}")
target_link_libraries(Main PUBLIC "${VULKAN_LIBS}")