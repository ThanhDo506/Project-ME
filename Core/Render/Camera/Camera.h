#ifndef CAMERA_H
#define CAMERA_H

#include "../../Components/Component.h"
#include "../RenderingSystem/Rendering.h"
#include "../RenderingSystem/FrameBuffer.h"

enum class CameraType {
	Perspective,
	Ortho,
	Physic
};

class Camera : public Component
{
public:
	Camera(CameraType type, 
		float near = 0.0001, 
		float far = 1000.0, 
		float fieldOfView = 60.0,
		int width = 1920, 
		int height = 1080, 
		GameObject* gameObject = nullptr);

	~Camera();

	float get_near_clipping() const;
	void set_near_clipping(float near);

	float get_far_clipping() const;
	void set_far_clipping(float far);

	void set_camera_type(CameraType newType);
	CameraType get_camera_type() const;

	int get_width() const;
	void set_width(int width);

	void set_height(int height);
	int get_height() const;

	glm::mat4 get_view_matrix() const;
	glm::mat4 get_projection_matrix() const;

	void set_render_to_texture(bool val);
	bool is_render_to_texture() const;

	Camera* Clone() const override;
private:
	bool			_isRenderToTexture = false;
	FrameBuffer*	_renderToTexture = nullptr;
	float			_nearClipping;
	float			_farClipping;
	float			_fieldOfView;
	int				_width, _height;
	CameraType		_cameraType;
};

#endif