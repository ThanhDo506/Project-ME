#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../common.h"
#include "../../third-party/stb/stb_image.h"
#include "exception"
#include <glm/glm.hpp>

enum MappingCubeType {
	CubicEnviroment,
	Cylindrical,
	SphereMap
};

enum TextureShape {
	Texture2D,
	Cube,
	Image
};

enum TextureAlphaSource {
	None,
	TextureAlpha,
	GrayScale
};

enum TextureFilterMode {
	PointFiltering,
	BilinearFiltering,
	TrilinearFiltering
};

enum TextureType {
	Default,
	Normal,
	LightMap,
	ShadowMask,
	SingleChannel
};

enum TextureWrapMode {
	Repeat,
	MirrorRepeat,
	ClampToEdge,
	ClampToBorder
};

struct TextureSetting {
	bool			flipVerticalTextureOnLoad	= false;
	/**
	 * @brief desired number of color channel.
	 * @brief 0: number of channels follow raw image.
	 */
	int				desiredChannel				= 0;
	bool			sRGB						= false;
	bool			alphaIsTransparency			= true;
	/**
	 * if maxMipmapsLevel >= 0 enable generate mipmap else generate no mipmaps.
	 */
	int				maxMipmapsLevel				= 4;
	glm::vec4		borderColor					= glm::vec4(0.0, 0.0, 0.0, 0.0);
	TextureShape	textureShape				= Texture2D;
	/**
	 * @brief Use this param when texture shape is Cube.
	 */
	MappingCubeType		mappingCubeType			= CubicEnviroment;
	TextureType			textureType				= Default;
	TextureFilterMode	textureFilter			= BilinearFiltering;
	TextureWrapMode		textureWrapMode			= Repeat;
	TextureAlphaSource	textureAlphaSrc			= TextureAlpha;
};

class Texture {
	friend class FrameBuffer;
private:
	/**
	 * true if color space is sRGB, false is linear.
	 */
	bool			_sRGB;
	TextureShape	_textureShape;
	TextureType		_textureType;
	GLenum			_internalFormat;
	/**
	 * Do not modify this attribute.
	 */
	GLuint			_id = 0;
	GLint			_width;
	GLint			_height;
	GLint			_numChannel;
	std::string		_path;

public:
	~Texture();
	/**
	 * @return true if color space is sRGB, false if linear.
	 */
	bool is_sRGB() const;

	void Clean();

	void bind_texture_unit(GLuint unit);

	static GLenum texture_shape_to_GL_target(TextureShape textureShape);

	bool load2DTexture(const char* path, TextureSetting& texSetting);

	/**
	 * Create cube texture.
	 * @brief
	 * Only support RGB format (no sRGB, etc).
	 * \param paths exactly 6 paths to 6 base image
	 * \param textureSetting
	 * \return init success or false
	 */
	bool loadCubeTexture(std::vector<const char*> paths, TextureSetting& textureSetting);

	bool loadHdr(const char* path, TextureSetting& textureSetting);

	std::string get_path() const;

private:
	void applySetting(const TextureSetting& textureSetting);
};

#endif
