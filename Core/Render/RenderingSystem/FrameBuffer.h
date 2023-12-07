#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../../common.h"
#include "../Object/Texture.h"
#include "RenderBuffer.h"
#include "../../Core/Render/Object/Shader.h"

class FrameBuffer
{
	friend class Rendering;
public:
	FrameBuffer(const unsigned int& width, const unsigned int& height, const RenderBuffer::InternalFormat& rboInternalFormat);
	~FrameBuffer();

	unsigned int get_width() const;
	unsigned int get_height() const;
	GLuint get_id() const;

	void render_frame_buffer_to_screen() const;

	GLuint get_color_texture_id() const;
	GLuint get_depth_stencil_texture() const;

	Shader* get_shader();
private:
	GLuint _id = 0;
	unsigned int _width, _height;
	Texture* _colorTexture = NULL;
	RenderBuffer* _renderBuffer = NULL;
	Shader* _shader = NULL;
	GLuint _vaoQuad = 0, _vboQuad = 0;


};
#endif
