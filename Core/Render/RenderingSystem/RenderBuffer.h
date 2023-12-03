#pragma once

#include "../../common.h"

class RenderBuffer
{
public:
	RenderBuffer(unsigned int width, unsigned int height);
	~RenderBuffer();

	unsigned int get_width() const;
	unsigned int get_height() const;
	GLuint get_id() const;
	void clean();
private:
	GLuint _id = -1;
	unsigned int _width, _height;
};

