#include "GUI.h"

GUI::GUI()
{
    _application = nullptr;
}

GUI& GUI::instance()
{
    static GUI instance;
    return instance;
}

void GUI::Init(Application* application, const char* glfwVersion)
{
    this->_application = application;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsLight();

    // set Font
    io.Fonts->AddFontFromFileTTF("Resources/fonts/Roboto-Medium.ttf", 16.0f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(application->_glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glfwVersion);
}

void GUI::Draw()
{
    canvas();
    ImGui::Render();
}

void GUI::Clean()
{
}

void GUI::canvas()
{
}
