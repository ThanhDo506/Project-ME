#include "Camera.h"

Camera::Camera(CameraType type, float near, float far, float fieldOfView, int width, int height, GameObject* gameObject)
	: Component(gameObject)
	, _cameraType(type)
	, _nearClipping(near)
	, _farClipping(far)
	, _fieldOfView(fieldOfView)
	, _width(width)
	, _height(height)
{
	Rendering::add_camera_to_registry(this);
}

Camera::~Camera()
{
	Rendering::remove_camera_from_registry(this);
}

float Camera::get_near_clipping() const
{
	return _nearClipping;
}

void Camera::set_near_clipping(float near)
{
	_nearClipping = near;
}

float Camera::get_far_clipping() const
{
	return 0.0f;
}

void Camera::set_far_clipping(float far)
{
	_farClipping = far;
}

void Camera::set_camera_type(CameraType newType)
{
	_cameraType = newType;
}

CameraType Camera::get_camera_type() const
{
	return _cameraType;
}

int Camera::get_width() const
{
	return _width;
}

void Camera::set_width(int width)
{
	_width = width;
}

void Camera::set_height(int height) 
{
	_height = height;
}

int Camera::get_height() const
{
	return _height;
}

glm::mat4 Camera::get_view_matrix() const
{
	Transform* transform = _gameObject->GetComponent<Transform>();
	return glm::lookAt(transform->position, transform->position + transform->forward(), transform->up());
}

glm::mat4 Camera::get_projection_matrix() const
{
	Transform* transform = _gameObject->GetComponent<Transform>();
	switch (_cameraType)
	{
	case CameraType::Perspective:
		return glm::perspective(glm::radians(this->_fieldOfView), _width * 1.0f / _height, _nearClipping, _farClipping);
		break;
	case CameraType::Ortho:
		return glm::ortho(0.0f, _width * 1.0f, 0.0f, _height * 1.0f, _nearClipping, _farClipping);
		break;
	case CameraType::Physic:
	default:
		return glm::perspective(glm::radians(this->_fieldOfView), _width * 1.0f / _height, _nearClipping, _farClipping);
	}
}

void Camera::set_render_to_texture(bool val)
{
	_isRenderToTexture = val;
}

bool Camera::is_render_to_texture() const
{
	return _isRenderToTexture;
}

Camera* Camera::Clone() const
{
	return new Camera(*this);
}
