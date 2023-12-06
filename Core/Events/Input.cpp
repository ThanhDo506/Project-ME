#include "Input.h"

Input& input = Input::instance();

Input::Input()
{
    p_application = nullptr;
}

void Input::init(Application* application)
{
    this->p_application = application;
    p_glfwWindow = application->_glfwWindow;
    this->_deltaMousePosition = glm::vec2(0.0);
    this->_lastMousePosition = glm::vec2(0.0);
    this->_mousePosition = glm::vec2(0.0);
}

void Input::update()
{
    if (glfwGetKey(Input::instance().p_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(Input::instance().p_glfwWindow, 1);
    }
    else if (glfwGetKey(p_glfwWindow, GLFW_KEY_1) == GLFW_PRESS)
    {
        glLineWidth(1.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (glfwGetKey(p_glfwWindow, GLFW_KEY_2) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (glfwGetKey(p_glfwWindow, GLFW_KEY_3) == GLFW_PRESS)
    {
        glPointSize(10.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (glfwGetKey(p_glfwWindow, GLFW_KEY_4) == GLFW_PRESS)
    {
        glPointSize(10.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}

void Input::reset()
{
    Input::instance()._deltaMousePosition = { 0, 0 };
    Input::instance()._lastMousePosition = { 0,0 };
}

void Input::clean()
{
    Input::instance().p_glfwWindow = nullptr;
    APP_INFO("Cleaning Input");
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void Input::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    glfwGetCursorPos(window, &Input::instance()._mousePosition.x, &Input::instance()._mousePosition.y);
    Input::instance()._deltaMousePosition = Input::instance()._mousePosition - Input::instance()._lastMousePosition;
    Input::instance()._lastMousePosition = Input::instance()._mousePosition;
}

Input& Input::instance()
{
    static Input instance;
    return instance;
}

glm::dvec2 Input::getMousePosition()
{
    return Input::instance()._mousePosition;
}

glm::dvec2 Input::getDeltaMousePosition()
{
    return Input::instance()._deltaMousePosition;
}

void Input::setMousePosition(glm::vec2 pos)
{
    Input::instance()._mousePosition = pos;
}

void Input::setDeltaMousePosition(glm::vec2 pos)
{
    Input::instance()._deltaMousePosition = pos;
}

void Input::lock_mouse_cursor(bool lock)
{
    Input::instance()._isLockCursor = lock;
}

bool Input::is_lock_mouse_cursor()
{
    return Input::instance()._isLockCursor;
}

void Input::reset_cursor_position()
{
    if (!Input::instance().p_glfwWindow)
        return;
    glfwSetCursorPos(Input::instance().p_glfwWindow, 1600/2, 900 / 2);
}

GLFWwindow* Input::getWindowManipulator() const
{
    return Input::instance().p_glfwWindow;
}
