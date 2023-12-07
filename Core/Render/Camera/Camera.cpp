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

	// this camera render image will be save in _frameBuffer
	this->_frameBuffer = new FrameBuffer(width, height, RenderBuffer::InternalFormat::DEPTH24_STENCIL8);

	//// for Diffuse-irradiance

	//init_cube();

	//TextureSetting ts = {
	//	.maxMipmapsLevel = 0,
	//	.textureWrapMode = ClampToEdge,
	//};
	//this->_hdrTexture.loadHdr("Resources/ibl/kloofendal_48d_partly_cloudy_puresky_2k.hdr", ts);
	//// init custome texture
	//glGenTextures(1, &this->_enviromentCubemapTexture._id);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->_enviromentCubemapTexture._id);
	//for (unsigned int i = 0; i < 6; ++i)
	//{
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
	//}
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	//static glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	//static glm::mat4 captureViews[] =
	//{
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	//	glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	//};

	//// pbr: convert HDR equirectangular environment map to cubemap equivalent
	//// ----------------------------------------------------------------------
	//_equirectangularToCubemapShader.Active();
	//this->_hdrTexture.bind_texture_unit(0);
	//_equirectangularToCubemapShader.SetInt("_EquirectangularMap", 0);
	//_equirectangularToCubemapShader.SetMat4("_ProjectionMatrix", captureProjection);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glViewport(0, 0, 512, 512);
	//glBindFramebuffer(GL_FRAMEBUFFER, this->_captureFbo->get_id());
	//for (unsigned int i = 0; i < 6; ++i)
	//{
	//	this->_equirectangularToCubemapShader.SetMat4("_ViewMatrix", captureViews[i]);
	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, this->_enviromentCubemapTexture._id, 0);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	render_cube();
	//}
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
			ImGui::DragFloat("Near", &this->_nearClipping, 0.005f, 0.001f, 1000.0f, "%.3f");
			ImGui::DragFloat("Far", &this->_farClipping, 10.0f, 1000.0f, 10000.0f, "%.f");
		}
		ImGui::TreePop();
	}
}

FrameBuffer* Camera::get_frame_buffer()
{
	return this->_frameBuffer;
}

void Camera::enable_frame_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->_frameBuffer->get_id());
}

void Camera::disable_frame_buffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
//
//void Camera::init_cube()
//{
//	if (this->_vaoCube)
//		return;
//	float vertices[] = {
//		// back face
//		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//		 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//		 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//		// front face
//		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//		 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//		// left face
//		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//		// right face
//		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//		 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
//		 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//		 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//		 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
//		 // bottom face
//		 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//		  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//		  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//		  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//		 -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//		 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//		 // top face
//		 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//		  1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//		  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
//		  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//		 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//		 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
//	};
//	glGenVertexArrays(1, &this->_vaoCube);
//	glGenBuffers(1, &this->_vaoCube);
//	// fill buffer
//	glBindBuffer(GL_ARRAY_BUFFER, this->_vaoCube);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	// link vertex attributes
//	glBindVertexArray(this->_vaoCube);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//void Camera::render_cube()
//{
//	glBindVertexArray(this->_vaoCube);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//}
