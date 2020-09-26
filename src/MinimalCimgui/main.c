#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>
// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Minimal cimgui Example"

static void error_callback(int e, const char *d) {
    fprintf(stderr, "Error %d: %s\n", e, d);
}

/* Platform */
static GLFWwindow *win;
struct ImGuiContext* ctx;
struct ImGuiIO* io;
struct ImVec4 clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };

void gui_init() {
    // IMGUI_CHECKVERSION();
    ctx = igCreateContext(NULL);
    io  = igGetIO();

    const char* glsl_version = "#version 330 core";
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    igStyleColorsDark(NULL);
}

void gui_terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    igDestroyContext(ctx);
}

void gui_render() {
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

void gui_update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();

    static bool show_demo_window = true;
    static bool show_another_window = false;

    {
        igBegin("Hello, World!", NULL, ImGuiWindowFlags_None);

        igText("This is some useful text.");

        igCheckbox("Demo Window", &show_demo_window);
        igCheckbox("Another Window", &show_another_window);

        static float f = 0.0f;
        igSliderFloat("float", &f, 0.0f, 1.0f, "%.3f", 1.0f);
        igColorEdit3("clear color", (float *)(&clear_color), ImGuiColorEditFlags_NoAlpha);

        static int counter = 0;
        if (igButton("Button", (struct ImVec2) { 0, 0 })) {
            counter++;
        }
        igSameLine(0, 5.f);
        igText("counter = %d", counter);

        igText("Application average %.3f ms/frame (%.1f FPS)", 1000.f / io->Framerate, io->Framerate);

        igEnd();
    }

    if (show_another_window) {
        igBegin("Another Window", &show_another_window, ImGuiWindowFlags_None);
        igText("Hello from another window!");
        if (igButton("Close Me", (struct ImVec2) { 0, 0 })) {
            show_another_window = false;
        }
        igEnd();
    }

    if (show_demo_window) {
        // // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. 
        // // Here we just want to make the demo initial state a bit more friendly!
        // igSetNextWindowPos((struct ImVec2){0,0}, ImGuiCond_FirstUseEver,(struct ImVec2){0,0} ); 
        igShowDemoWindow(NULL);
    }
}


int main(int argc, char** argv) {
    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "[GFLW] failed to init!\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac

    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!win) {
        fprintf(stderr, "Failed to initialize window with OpenGL 3.3 Core Profile\n");
        return 1;
    }

    glfwMakeContextCurrent(win);
    int err = gladLoadGL();
    if (err == 0){
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    gui_init();

    // glfwSetWindowSizeCallback(win, onResize);
    int width, height;
    glfwGetWindowSize(win, &width, &height);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!glfwWindowShouldClose(win)) {
        /* Input */
        glfwPollEvents();

        gui_update();

        /* Draw */
        glfwGetWindowSize(win, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

        gui_render();

        glfwSwapBuffers(win);
    }

    gui_terminate();
    glfwTerminate();
}
