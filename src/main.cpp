// main.cpp
#include <iostream>
#include <memory>
#include <cmath>
#include <vector>

// Apache Arrow
#include <arrow/api.h>

// GLAD must be included before GLFW.
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Dear ImGui and backends
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// ImPlot for plotting
#include "implot.h"

int main() {
    // ------------------------------
    // Test Apache Arrow: Build a simple Int32 array.
    // ------------------------------
    arrow::Int32Builder builder;
    arrow::Status status;

    status = builder.Append(10);
    if (!status.ok()) {
        std::cerr << "Error appending 10: " << status.ToString() << std::endl;
        return -1;
    }
    status = builder.Append(20);
    if (!status.ok()) {
        std::cerr << "Error appending 20: " << status.ToString() << std::endl;
        return -1;
    }
    status = builder.Append(30);
    if (!status.ok()) {
        std::cerr << "Error appending 30: " << status.ToString() << std::endl;
        return -1;
    }

    std::shared_ptr<arrow::Array> array;
    status = builder.Finish(&array);
    if (!status.ok()) {
        std::cerr << "Error finishing the array: " << status.ToString() << std::endl;
        return -1;
    }
    std::cout << "Apache Arrow array: " << array->ToString() << std::endl;

    // ------------------------------
    // Initialize GLFW.
    // ------------------------------
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    }

    // Set OpenGL version (here using 3.0 as an example)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // Optionally set profile, e.g., GLFW_OPENGL_CORE_PROFILE

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Test Arrow, ImGui, ImPlot, OpenGL, GLFW3", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // ------------------------------
    // Initialize GLAD to load OpenGL functions.
    // ------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    // ------------------------------
    // Initialize ImGui and ImPlot.
    // ------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Initialize the ImGui GLFW and OpenGL3 backends.
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // ------------------------------
    // Main application loop.
    // ------------------------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start new ImGui frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create a window that demonstrates ImGui and ImPlot.
        ImGui::Begin("Test Window");
        ImGui::Text("Hello, world! This window tests ImGui and ImPlot.");

        // Plot a simple sine wave using ImPlot.
        if (ImPlot::BeginPlot("Simple Sine Wave Plot")) {
            constexpr int count = 100;
            static float xs[count];
            static float ys[count];
            for (int i = 0; i < count; i++) {
                xs[i] = static_cast<float>(i);
                ys[i] = std::sinf(i * 0.1f);
            }
            ImPlot::PlotLine("Sine Wave", xs, ys, count);
            ImPlot::EndPlot();
        }
        ImGui::End();

        // Render ImGui.
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // ------------------------------
    // Cleanup
    // ------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown(); 
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
