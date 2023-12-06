#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(unsigned int width, unsigned int height)
	: _width(width), _height(height)
{
	glGenRenderbuffers(1, &_id);
	glBindRenderbuffer(GL_RENDERBUFFER, _id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &_id);
}

unsigned int RenderBuffer::get_width() const
{
	return _width;
}

unsigned int RenderBuffer::get_height() const
{
	return _height;
}

GLuint RenderBuffer::get_id() const
{
	return _id;
}

void RenderBuffer::clean()
{
	glDeleteRenderbuffers(1, &_id);
	_width = _height = 0;
}
