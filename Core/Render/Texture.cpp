#include "Texture.h"

Texture::Texture(const char* path, TextureSetting& texSetting)
{
	load(path, texSetting);
}

Texture::Texture(std::vector<const char*> paths, TextureSetting& texSetting)
{
	load(paths, texSetting);
}

void Texture::load(const char* path, TextureSetting& texSetting)
{
	this->_texShape = TextureShape::Texture2D;
	this->_texType = texSetting.texType;
	this->_sRGB = texSetting.sRGB;
	stbi_set_flip_vertically_on_load(texSetting.flipTextureOnLoad);
	unsigned char* imageData = stbi_load(path, &this->_width, &this->_height, &this->_numChannel, texSetting.desiredChannel);
	if (imageData == nullptr) {
		stbi_image_free(imageData);
		APP_ERROR("Could not read %s", path);
		throw errno;
	}
	GLenum dataFormat;
	switch (this->_numChannel)
	{
	case 1:
		this->_internalFormat = GL_R8;
		dataFormat = GL_RED;
		break;
	case 2:
		this->_internalFormat = GL_RG8;
		dataFormat = GL_RG;
		break;
	case 3:
		this->_internalFormat = this->_sRGB ? GL_SRGB8 : GL_RGB8;
		dataFormat = GL_RGB;
		break;
	case 4:
		this->_internalFormat = this->_sRGB ? GL_SRGB8_ALPHA8 : GL_RGBA8;
		dataFormat = GL_RGBA;
		break;
	default:
		stbi_image_free(imageData);
		APP_ERROR("Unsupported texture format!");
		throw errno;
		break;
	}

	glGenTextures(1, &this->_id);
	glBindTexture(GL_TEXTURE_2D, this->_id);

	glTexImage2D(GL_TEXTURE_2D, 0, this->_internalFormat, _width, _height, 0,
		dataFormat, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);


	_initialized = true;
}

void Texture::load(std::vector<const char*> paths, TextureSetting& texSetting)
{
}

void Texture::Clean() 
{
}

void Texture::bindTextureUnit(GLuint& unit, GLuint& textureId) 
{
}

void Texture::load2DTexture(const char* path, TextureSetting& texSetting)
{
}

void Texture::loadCubeTexture(const char* path, TextureSetting& texSetting)
{
}

void Texture::applySetting(const TextureSetting& textureSetting)
{

}
