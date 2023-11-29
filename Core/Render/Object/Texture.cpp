#include "Texture.h"
#include <glm/gtc/type_ptr.hpp>

Texture::~Texture()
{
	this->Clean();
}

bool Texture::is_sRGB() const
{
	return this->_sRGB;
}

void Texture::Clean()
{
	glDeleteTextures(1, &_id);
}

void Texture::bind_texture_unit(GLuint unit) 
{
	glActiveTexture(GL_TEXTURE0 + unit);

	switch (_textureShape)
	{
	case Texture2D:
		glBindTexture(GL_TEXTURE_2D, _id);
		break;
	case Cube:
		glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
		break;
	case Image:
		glBindImageTexture(unit, _id, 0, GL_FALSE, 0, GL_READ_WRITE, _internalFormat);
		break;
	default:
		APP_ERROR("Invalid texture shape");
		throw std::runtime_error("Invalid texture shape");
	}
}

GLenum Texture::texture_shape_to_GL_target(TextureShape textureShape)
{
	switch (textureShape) {
	case Texture2D:
		return GL_TEXTURE_2D;
	case Cube:
		return GL_TEXTURE_CUBE_MAP;
	default:
		APP_ERROR("Invalid texture shape");
		return GL_INVALID_ENUM;
	}
}

bool Texture::load2DTexture(const char* path, TextureSetting& textureSetting)
{
	if (_id != 0) {
		APP_WARN("This texture has been initialized, if want to recreate please use Clean() first.");
		return false;
	}

	this->_textureShape = TextureShape::Texture2D;
	this->_textureType = textureSetting.textureType;
	this->_sRGB = textureSetting.sRGB;
	stbi_set_flip_vertically_on_load(textureSetting.flipVerticalTextureOnLoad);
	unsigned char* imageData = stbi_load(path, &this->_width, &this->_height, &this->_numChannel, textureSetting.desiredChannel);
	if (imageData == nullptr) {
		stbi_image_free(imageData);
		APP_ERROR("Could not read %s", path);
		return false;
	}
	GLenum dataFormat;
	switch (this->_numChannel)
	{
	case 1:
		_internalFormat = GL_R8;
		dataFormat = GL_RED;
		break;
	case 2:
		_internalFormat = GL_RG8;
		dataFormat = GL_RG;
		break;
	case 3:
		_internalFormat = _sRGB ? GL_SRGB8 : GL_RGB8;
		dataFormat = GL_RGB;
		break;
	case 4:
		_internalFormat = _sRGB ? GL_SRGB8_ALPHA8 : GL_RGBA8;
		dataFormat = GL_RGBA;
		break;
	default:
		stbi_image_free(imageData);
		APP_ERROR("Unsupported texture format!");
		return false;
	}
	
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, imageData);
	if (textureSetting.maxMipmapsLevel >= 0)
		glGenerateMipmap(GL_TEXTURE_2D);

	applySetting(textureSetting);
	stbi_image_free(imageData);
	return true;
}

bool Texture::loadCubeTexture(std::vector<const char*> paths, TextureSetting& textureSetting)
{
	if (_id != 0) {
		APP_WARN("This texture has been initialized, if want to recreate please use Clean() first.");
		return false;
	}
	if (paths.size() != 6)
	{
		APP_ERROR("Must pass exactly 6 faces to loadCubeTexture() fn.");
		return false;
	}
	_textureShape = TextureShape::Cube;
	
	_internalFormat = GL_RGB8; // Cubemaps must be RGB.

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	stbi_set_flip_vertically_on_load(textureSetting.flipVerticalTextureOnLoad);

	int width, height, numChannels;
	bool initialized = false;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		unsigned char* data = stbi_load(paths[i], &width, &height,
			&numChannels, textureSetting.desiredChannel);
		// Error handling.
		if (data == nullptr)
		{
			stbi_image_free(data);
			APP_ERROR("Load texture failure!");
			return false;
		}
		if (numChannels != 3)
		{
			stbi_image_free(data);
			APP_ERROR("Unsupported texture format.");
			return false;
		}
		if (!initialized)
		{
			if (width != height)
			{
				APP_WARN("Texture size doesn't a square");
			}
			_width = width;
			_height = height;
			_numChannel = numChannels;
		}
		else if (width != _width || height != _height)
		{
			APP_WARN("Texture %s is different size from first texture.", paths[i]);
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			_internalFormat, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	applySetting(textureSetting);
	return true;
}

bool Texture::loadHdr(const char* path, TextureSetting& textureSetting)
{
	if (_id != 0) {
		APP_WARN("This texture has been initialized, if want to recreate please use Clean() first.");
		return false;
	}
	_textureShape = TextureShape::Texture2D;

	stbi_set_flip_vertically_on_load(textureSetting.flipVerticalTextureOnLoad);
	float* data = stbi_loadf(path, &_width, &_height, &_numChannel, textureSetting.desiredChannel);

	if (data == nullptr)
	{
		stbi_image_free(data);
		APP_ERROR("Load image %s failure.", path);
		return false;
	}

	GLenum dataFormat;
	if (_numChannel == 1)
	{
		_internalFormat = GL_R16F;
		dataFormat = GL_RED;
	}
	else if (_numChannel == 2)
	{
		_internalFormat = GL_RG16F;
		dataFormat = GL_RG;
	}
	else if (_numChannel == 3)
	{
		_internalFormat = GL_RGB16F;
		dataFormat = GL_RGB;
	}
	else if (_numChannel == 4)
	{
		_internalFormat = GL_RGBA16F;
		dataFormat = GL_RGBA;
	}
	else
	{
		stbi_image_free(data);
		APP_ERROR("Texture %s contained unsupported number of channels: %d", path, _numChannel);
		return false;
	}

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, dataFormat, GL_FLOAT, data);

	applySetting(textureSetting);
	stbi_image_free(data);

	return true;
}

std::string Texture::get_path() const
{
	return _path;
}

void Texture::applySetting(const TextureSetting& textureSetting)
{
	GLenum target = texture_shape_to_GL_target(_textureShape);
	switch (textureSetting.textureFilter)
	{
	case PointFiltering:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case BilinearFiltering:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TrilinearFiltering:
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}

	switch (textureSetting.textureWrapMode)
	{
	case TextureWrapMode::Repeat:
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		if (_textureShape == TextureShape::Cube)
		{
			glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_REPEAT);
		}
		break;
	case TextureWrapMode::ClampToEdge:
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if (_textureShape == TextureShape::Cube)
		{
			glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}
		break;
	case TextureWrapMode::ClampToBorder:
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		if (_textureShape == TextureShape::Cube)
		{
			glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
		}
		glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(textureSetting.borderColor));
		break;
	}
}
