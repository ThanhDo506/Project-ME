#ifndef MATERIAL_H
#define MATERIAL_H

#include <utility>
#include "../utilities/Logger.h"
#include <glm/glm.hpp>
#include "Texture.h"

enum RenderFace {
	Front,
	Back,
	Both
};

enum SurfaceType {
	Opaque,
	Transparent
};

enum BlendingMode {
	Alpha,
	Premultiply,
	Additive,
	Multiply
};

class Material {

private:
	Texture		_diffuseMap;
	Texture		_roughnessMap;
	Texture		_metallicMap;
	Texture		_aoMap;
	Texture		_normalMap;
	Texture		_emissionMap;
	float		_metallic;
	float		_smoothness;
	float		_aoStrength;
	float		_alphaClipping;
	glm::vec4	_reflectColor;
	bool		_useEmissionMap;
	bool		_useMetallicMap;
	bool		_receivedShadow;
	std::pair<float, float> tilling;
	std::pair<float, float> offset;
};

#endif
