#ifndef TEXTURE_H
#define TEXTURE_H

#include "../common.h"
#include "../../third-party/stb/stb_image.h"

enum MappingCubeType {
	CubicEnviroment,
	Cylindrical,
	SphereMap
};

enum TextureShape {
	Texture2D,
	Cube
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
	Clamp2Edge,
	Clamp2Border
};

struct TextureSetting {
	bool			flipTextureOnLoad	= false;
	/**
	 * @brief desired number of color channel.
	 * @brief 0: number of channels follow raw image.
	 */
	int				desiredChannel		= 0;
	bool			sRGB				= false;
	bool			alphaIsTransparency = true;
	int				maxMipmapsLevel		= 4;
	TextureShape	texShape			= Texture2D;
	/**
	 * @brief Use this param when texture shape is Cube.
	 */
	MappingCubeType		mappingCubeType = CubicEnviroment;
	TextureType			texType			= Default;
	TextureFilterMode	texFilter		= PointFiltering;
	TextureWrapMode		texWrapMode		= Repeat;
	TextureAlphaSource	texAlphaSrc		= TextureAlpha;
};

class Texture {

private:
	bool			_initialized = false;
	bool			_sRGB;
	TextureShape	_texShape;
	TextureType		_texType;
	GLenum			_internalFormat;
	GLuint			_id;
	GLint			_width;
	GLint			_height;
	GLint			_numChannel;
	const char*		_path;

public:
	Texture(const char* path, TextureSetting& texSetting);

	Texture(std::vector<const char*> paths, TextureSetting& texSetting);



	/**
	 * @brief Clean up from GPU.
	 */
	void Clean();

	void bindTextureUnit(GLuint& unit, GLuint& textureId);

private:
	void load(const char* path, TextureSetting& texSetting);

	void load(std::vector<const char*> paths, TextureSetting& texSetting);

	void load2DTexture(const char* path, TextureSetting& texSetting);

	void loadCubeTexture(const char* path, TextureSetting& texSetting);

	void applySetting(const TextureSetting& textureSetting);
};

#endif
