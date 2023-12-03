#ifndef INPUT_H
#define INPUT_H

#include "../common.h"
#include <glm/glm.hpp>
#include "../Application.h"

class Input
{
    friend class Application;
public:
    static Input& instance();
    static glm::dvec2 getMousePosition();
    static glm::dvec2 getDeltaMousePosition();

    static void setMousePosition(glm::vec2 pos);
    static void setDeltaMousePosition(glm::vec2 pos);
    static void lock_mouse_cursor(bool lock);
    static bool is_lock_mouse_cursor();
    static void reset_cursor_position();
    GLFWwindow* getWindowManipulator() const;
private:
    Input(const Input& obj) = delete;
    void operator=(const Input& obj) = delete;
    Input();

    void init(Application* application);

    void update();
    void reset();
    void clean();

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

    Application* p_application;
    GLFWwindow* p_glfwWindow;
    glm::dvec2   _mousePosition = { 0.0,0.0 };
    glm::dvec2   _lastMousePosition = { 0.0,0.0 };
    glm::dvec2   _deltaMousePosition = { 0.0,0.0 };
    bool        _isLockCursor = false;
};
#endif
