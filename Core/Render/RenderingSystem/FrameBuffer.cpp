#include "FrameBuffer.h"

static unsigned int c = 0;

FrameBuffer::FrameBuffer(const unsigned int& width, const unsigned int& height,  const RenderBuffer::InternalFormat& rboInternalFormat, const bool& hasColoredFBO)
	: _width(width), _height(height), _hasColoredFBO(hasColoredFBO)
{
	constexpr float QUAD_VERTICES[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// init frame buffer
	glGenFramebuffers(1, &this->_id);
	glBindFramebuffer(GL_FRAMEBUFFER, this->_id);

	if (this->_hasColoredFBO) {
		// init color texture
		this->_colorTexture = new Texture("Frame Buffer Texture " + std::to_string(c++));
		_colorTexture->_textureShape = Texture2D;
		_colorTexture->_textureType = Default;
		_colorTexture->_internalFormat = GL_RGB;
		_colorTexture->_width = width;
		_colorTexture->_height = height;
		_colorTexture->_numChannel = 3;
		glGenTextures(1, &_colorTexture->_id);
		glBindTexture(GL_TEXTURE_2D, _colorTexture->_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// attach color texture to frame buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_colorTexture->_id, 0);
	}
	
	// init and attach depth buffer to frame buffer
	this->_renderBuffer = new RenderBuffer(_width, _height, rboInternalFormat);
	switch (rboInternalFormat)
	{
	case RenderBuffer::InternalFormat::DEPTH24_STENCIL8:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->get_id());
		break;
	case RenderBuffer::InternalFormat::DEPTH_COMPONENT24:
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->get_id());
		break;
	default:
		break;
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		APP_ERROR("Failure to initialize Frame Buffer.");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// init shader to render quad
	this->_shader = new Shader("FBO", "Resources/GLSL/fbo.vert", "Resources/GLSL/fbo.frag");

	// Init quad
	glGenVertexArrays(1, &this->_vaoQuad);
	glGenBuffers(1, &this->_vboQuad);

	glBindVertexArray(this->_vaoQuad);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_VERTICES), &QUAD_VERTICES, GL_STATIC_DRAW);

	// bind attribute
	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normal
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind to avoid modified
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	delete this->_colorTexture;
	delete this->_renderBuffer;
	glDeleteVertexArrays(1, &this->_vaoQuad);
	glDeleteBuffers(1, &this->_vboQuad);
	glDeleteBuffers(1, &this->_id);
}

unsigned int FrameBuffer::get_width() const
{
	return _width;
}

unsigned int FrameBuffer::get_height() const
{
	return _height;
}

GLuint FrameBuffer::get_id() const
{
	return this->_id;;
}

void FrameBuffer::render_frame_buffer_to_screen() const
{
	this->_shader->Active();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->get_color_texture_id());
	glBindVertexArray(this->_vaoQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

GLuint FrameBuffer::get_color_texture_id() const
{
	return this->_colorTexture->_id;
}

GLuint FrameBuffer::get_depth_stencil_texture() const
{
	return this->_renderBuffer->get_id();
}

Shader* FrameBuffer::get_shader()
{
	return this->_shader;
}
