#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
	: _width(width), _height(height)
{
	// init color texture
	this->_colorTexture = new Texture();
	_colorTexture->_textureShape = Texture2D;
	_colorTexture->_textureType = Default;
	_colorTexture->_internalFormat = GL_RGB;
	_colorTexture->_width = width;
	_colorTexture->_height = height;
	_colorTexture->_numChannel = 3;
	glGenTextures(1, &_colorTexture->_id);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexture->_id, 0);

	// init and attach render buffer
	this->_renderBuffer = new RenderBuffer(_width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->get_id());

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		APP_ERROR("Failure to initialize Frame Buffer.");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	delete this->_colorTexture;
	delete this->_renderBuffer;
}

unsigned int FrameBuffer::get_width() const
{
	return _width;
}

unsigned int FrameBuffer::get_height() const
{
	return _height;
}
