#include "Camera.h"
#include "../../../third-party/imgui/imgui.h"

Camera::Camera(CameraType type, float near, float far, float fieldOfView, int width, int height, GameObject* gameObject)
	: Component(nullptr)
	, _cameraType(type)
	, _nearClipping(near)
	, _farClipping(far)
	, _fieldOfView(fieldOfView)
	, _width(width)
	, _height(height)
{
	Rendering::add_camera_to_registry(this);
	attach_to_gameObject(gameObject);

	this->_frameBuffer = new FrameBuffer(width, height);
}

Camera::~Camera()
{
	delete this->_frameBuffer;
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

unsigned int Camera::get_width() const
{
	return _width;
}

void Camera::set_width(const unsigned int& width)
{
	_width = width;
}

void Camera::set_height(const unsigned int& height)
{
	_height = height;
}

unsigned int Camera::get_height() const
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
		return glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, _nearClipping, _farClipping);
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

void Camera::OnGui()
{
	if (ImGui::TreeNode("Camera")) {
		if (ImGui::TreeNode("Projection")) {
			// Camera type
			static const char*	cameraType[] = { "Perspective", "Orthographic", "Physic" };
			static int			currentItem = 0;
			if (ImGui::Combo("Camera type", &currentItem, cameraType, IM_ARRAYSIZE(cameraType))) {
				switch (currentItem)
				{
				case CameraType::Perspective:
					this->_cameraType = Perspective;
					break;
				case CameraType::Ortho:
					this->_cameraType = Ortho;
					break;
				case CameraType::Physic:
					this->_cameraType = Physic;
					break;
				default: break;
				}
			}
			if (this->_cameraType != Ortho) {
				ImGui::DragFloat("Fov", &this->_fieldOfView, 1, 0, 175, "%.f");
			}
			ImGui::DragFloat("Near", &this->_nearClipping, 0.005, 0.001, 1000, "%.3f");
			ImGui::DragFloat("Far", &this->_farClipping, 10, 1000, 10000, "%.f");
		}
		ImGui::TreePop();
	}
}

void Camera::enable_frame_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer->get_id());
}

void Camera::disable_frame_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
