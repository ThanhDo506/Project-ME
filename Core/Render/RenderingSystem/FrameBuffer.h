#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "../../common.h"
#include "../Object/Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	unsigned int get_width() const;
	unsigned int get_height() const;

private:
	GLint _id = -1;
	unsigned int _width, _height;
	Texture* _colorTexture;
	RenderBuffer* _renderBuffer;
};
#endif
