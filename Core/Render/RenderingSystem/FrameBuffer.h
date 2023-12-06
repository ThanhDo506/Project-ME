#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../../common.h"
#include "../Object/Texture.h"
#include "RenderBuffer.h"
#include "../../Core/Render/Object/Shader.h"

constexpr float QUAD_VERTICES[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};

class FrameBuffer
{

public:
	FrameBuffer(const unsigned int& width, const unsigned int& height);
	~FrameBuffer();

	unsigned int get_width() const;
	unsigned int get_height() const;
	GLuint get_id() const;

	void render_frame_buffer_to_screen() const;

	GLuint get_color_texture_id() const;
	GLuint get_depth_stencil_texture() const;
private:
	GLuint _id = 0;
	unsigned int _width, _height;
	Texture* _colorTexture = NULL;
	RenderBuffer* _renderBuffer = NULL;
	Shader* _shader = NULL;
	GLuint _vaoQuad = 0, _vboQuad = 0;
};
#endif
