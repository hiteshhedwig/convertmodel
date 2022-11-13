
#include "ncnnoptimize.h"
#include "ncnnreader.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

// ncnn public header
#include "layer.h"
#include "layer_type.h"
#include "net.h"

// gui headers
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

// Our state
static bool show_demo_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void my_display_code()
{
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void glut_display_func()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    my_display_code();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    // if (argc < 6)
    // {
    //     fprintf(stderr, "usage: %s [inparam] [inbin] [outparam] [outbin] [flag] [cutstart] [cutend]\n", argv[0]);
    //     return -1;
    // }

    // const char* inparam = argv[1];
    // const char* inbin = argv[2];
    // const char* outparam = argv[3];
    // const char* outbin = argv[4];
    // int flag = atoi(argv[5]);
    // const char* cutstartname = nullptr;
    // const char* cutendname = nullptr;

    // if (argc > 6)
    // {
    //     cutstartname = argv[6];
    // }

    // if (argc > 7)
    // {
    //     cutendname = argv[7];
    // }

    // NetOptimize optimizer;

    // if (flag == 65536 || flag == 1)
    // {
    //     optimizer.storage_type = 1;
    // }
    // else
    // {
    //     optimizer.storage_type = 0;
    // }

    // optimizer.load_param(inparam);

    // if (strcmp(inbin, "null") == 0)
    // {
    //     DataReaderFromEmpty dr;
    //     optimizer.load_model(dr);
    //     optimizer.gen_random_weight = true;
    // }
    // else
    //     optimizer.load_model(inbin);

    // if (optimizer.set_cutparam(cutstartname, cutendname) < 0)
    // {
    //     return -1;
    // }

    // optimizer.fuse_batchnorm_scale();
    // optimizer.fuse_convolution_batchnorm();
    // optimizer.fuse_convolution_mul();
    // optimizer.fuse_convolution_add();
    // optimizer.fuse_convolutiondepthwise_batchnorm();
    // optimizer.fuse_convolutiondepthwise_mul();
    // optimizer.fuse_convolutiondepthwise_add();
    // optimizer.fuse_deconvolution_batchnorm();
    // optimizer.fuse_deconvolution_mul();
    // optimizer.fuse_deconvolution_add();
    // optimizer.fuse_deconvolutiondepthwise_batchnorm();
    // optimizer.fuse_innerproduct_batchnorm();
    // optimizer.fuse_innerproduct_add();
    // optimizer.fuse_innerproduct_dropout();

    // optimizer.replace_reduction_with_global_pooling();
    // optimizer.replace_prelu_with_leaky_relu();

    // optimizer.fuse_convolution_activation();
    // optimizer.fuse_convolutiondepthwise_activation();
    // optimizer.fuse_deconvolution_activation();
    // optimizer.fuse_deconvolutiondepthwise_activation();
    // optimizer.fuse_innerproduct_activation();
    // optimizer.fuse_memorydata_binaryop();
    // optimizer.fuse_binaryop_eltwise();

    // optimizer.eliminate_dropout();
    // optimizer.eliminate_pooling1x1();
    // optimizer.eliminate_noop();
    // optimizer.eliminate_split();
    // optimizer.eliminate_flatten_after_global_pooling();
    // optimizer.eliminate_reshape_after_global_pooling();
    // optimizer.eliminate_reshape_before_binaryop();

    // optimizer.replace_convolution_with_innerproduct_after_global_pooling();
    // optimizer.replace_convolution_with_innerproduct_after_innerproduct();

    // optimizer.eliminate_flatten_after_innerproduct();
    // optimizer.eliminate_orphaned_memorydata();

    // optimizer.shape_inference();

    // optimizer.estimate_memory_footprint();

    // optimizer.save(outparam, outbin);


    // Create GLUT window
    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Dear ImGui GLUT+OpenGL2 Example");

    // Setup GLUT display function
    // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
    glutDisplayFunc(glut_display_func);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    // FIXME: Consider reworking this example to install our own GLUT funcs + forward calls ImGui_ImplGLUT_XXX ones, instead of using ImGui_ImplGLUT_InstallFuncs().
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}