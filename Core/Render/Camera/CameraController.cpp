#include "CameraController.h"

CameraController::CameraController(float speed, float sensitivityX, float sensitivityY)
	: Component(nullptr),
	_speed(speed), 
	_sensitivityX(sensitivityX), _sensitivityY(sensitivityY),
    _isForcus(false),
    rotationX(0), rotationY(0)
{
}

void CameraController::Update()
{
	if (!_camera)
		return;
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_F1) == GLFW_PRESS) {
        _isForcus = !_isForcus;
        if (_isForcus) {
            APP_INFO("[CAMERA CONTROLLER] Enable camera forcus.");
            glfwSetInputMode(Input::instance().getWindowManipulator(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            int width, height;
            glfwGetFramebufferSize(Input::instance().getWindowManipulator(), &width, &height);
            glfwSetCursorPos(Input::instance().getWindowManipulator(), width * 1.0f / 2, height * 1.0f / 2);
        } else {
            APP_INFO("[CAMERA CONTROLLER] Disable camera forcus.");
            glfwSetInputMode(Input::instance().getWindowManipulator(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (glfwGetMouseButton(Input::instance().getWindowManipulator(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
        _isForcus = !_isForcus;
        if (_isForcus) {
            APP_INFO("[CAMERA CONTROLLER] Enable camera forcus.");
            glfwSetInputMode(Input::instance().getWindowManipulator(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            int width, height;
            glfwGetFramebufferSize(Input::instance().getWindowManipulator(), &width, &height);
            glfwSetCursorPos(Input::instance().getWindowManipulator(), width * 1.0f / 2, height * 1.0f / 2);
        } else {
            APP_INFO("[CAMERA CONTROLLER] Disable camera forcus.");
            glfwSetInputMode(Input::instance().getWindowManipulator(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (this->_isForcus)
        camera_rotation();
    camera_movement();
}

void CameraController::set_camera(Camera* camera)
{
    this->_camera = camera;
}

CameraController* CameraController::Clone() const
{
    return new CameraController(*this);
}

void CameraController::camera_movement()
{
    Transform* t = _camera->gameObject->GetComponent<Transform>();
    // Handles key inputs
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_W) == GLFW_PRESS)
    {
        t->position += _speed * t->forward() * static_cast<float>(Time::get_delta_time());
    }
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_A) == GLFW_PRESS)
    {
        t->position += _speed * t->right() * static_cast<float>(Time::get_delta_time());
    }
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_S) == GLFW_PRESS)
    {
        t->position += _speed * -t->forward() * static_cast<float>(Time::get_delta_time());
    }
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_D) == GLFW_PRESS)
    {
        t->position += _speed * -t->right() * static_cast<float>(Time::get_delta_time());
    }
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        t->position += _speed * t->up() * static_cast<float>(Time::get_delta_time());
    }
    if (glfwGetKey(Input::instance().getWindowManipulator(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        t->position += _speed * -t->up() * static_cast<float>(Time::get_delta_time());
    }
}

void CameraController::camera_rotation()
{
        glm::dvec2 currentMousePos;
        glfwGetCursorPos(Input::instance().getWindowManipulator(), &currentMousePos.x, &currentMousePos.y);
        int width, height;
        glfwGetFramebufferSize(Input::instance().getWindowManipulator(), &width, &height);
        glm::dvec2 delta = glm::dvec2(width / 2, height / 2) - currentMousePos;

        rotationX -= _sensitivityY * delta.y * static_cast<float>(Time::get_delta_time()) * 0.01f;
        rotationY += _sensitivityX * delta.x * static_cast<float>(Time::get_delta_time()) * 0.01f;

        if (rotationX <= -89.5f)
        {
            rotationX = -89.5;
        }
        else if (rotationX >= 89.5f)
        {
            rotationX = 89.5f;
        }
        _camera->gameObject->GetComponent<Transform>()->rotation = Transform::euler_angles_to_quaternion(rotationX, rotationY, 0.0f);
        glfwSetCursorPos(Input::instance().getWindowManipulator(), width / 2, height / 2);
}
