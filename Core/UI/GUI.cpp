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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Clean()
{
    this->root = nullptr;
}

void GUI::canvas()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static ImGuiIO& io = ImGui::GetIO();
    (void)io;
    if (_showDemoWidget) {
        ImGui::ShowDemoWindow(&_showDemoWidget);
    }
    {
        if (ImGui::Begin("Setting"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            if (ImGui::TreeNode("Other setting"))
            {
                ImGui::Checkbox("Show style editor", &this->_showStyleEditor);
                if (this->_showStyleEditor)
                    ImGui::ShowStyleEditor();
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }
    {
        if (ImGui::Begin("Hierachy")) {
            if (this->root) {
                print_hierachy(root);
            }
        }
        ImGui::End();
    }
    {
        if (this->selectedGameObject) {
            if (ImGui::Begin("Components")) {
                ImGui::Checkbox("Active", &this->selectedGameObject->_active);
                for (auto component : this->selectedGameObject->_components) {
                    component.second->OnGui();
                }
            }
            ImGui::End();
        }
    }
    {
        if (ImGui::Begin("Texture Manager")) {
            static int _id = 1;
            ImGui::SliderInt("Texture id", &_id, 0, 20);
            ImGui::Image((void*)static_cast<intptr_t>(_id), ImVec2(128, 128));


            for (auto texture : TextureManager::instance()._textureRegistry) {
                Texture* t = texture.second;
                ImGui::TextColored(ImVec4(3.0/255, 140.0/255, 252.0/255, 1.0), "%s (id: %d)", texture.first.c_str(), t->get_id());
                ImGui::Text("Size: %dx%d", t->_width, t->_height);
                ImGui::Text("Shape: %s", Texture::to_string(t->_textureShape).c_str());
                ImGui::Image((void*)static_cast<intptr_t>(t->get_id()), ImVec2(128 * t->_width / t->_height, 128));
            }
            ImGui::End();
        }
    }
}

void GUI::print_hierachy(GameObject* root)
{
    if (ImGui::TreeNodeEx(root->name.c_str())) {
        if (ImGui::IsItemClicked()) {
            this->selectedGameObject = root;
        }
        for (auto child : root->_children) {
            print_hierachy(child);
        }
        ImGui::TreePop();
    }
}

void GUI::print_components(GameObject* gameObject)
{
    ImGui::Begin("Components");
    for (auto component : gameObject->_components) {
        
    }
    ImGui::End();
}
