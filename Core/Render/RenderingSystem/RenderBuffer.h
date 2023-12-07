#pragma once

#include "../../common.h"



class RenderBuffer
{
public:
	enum class InternalFormat {
		DEPTH24_STENCIL8,
		DEPTH_COMPONENT24
	};

	RenderBuffer(unsigned int width, unsigned int height, const InternalFormat& internalFormat);
	~RenderBuffer();

	unsigned int get_width() const;
	unsigned int get_height() const;
	GLuint get_id() const;
	void clean();
	GLenum get_gl_internal_format() const;
private:
	GLuint			_id = 0;
	unsigned int	_width, _height;
	GLenum			_internalFormat;
};

