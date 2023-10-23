#include "Material.h"

Texture Material::get_diffuse_map() const
{
    return _diffuseMap;
}

void Material::set_diffuse_map(Texture diffuseMap)
{
    _diffuseMap = diffuseMap;
}

Texture Material::get_roughness_map() const
{
    return _roughnessMap;
}

void Material::set_roughness_map(Texture roughnessMap)
{
    _roughnessMap = roughnessMap;
}

Texture Material::get_metallic_map() const
{
    return _metallicMap;
}

void Material::set_metallic_map(Texture metallicMap)
{
    _metallicMap = metallicMap;
}

Texture Material::get_ao_map() const
{
    return _aoMap;
}

void Material::set_ao_map(Texture aoMap)
{
    _aoMap = aoMap;
}

Texture Material::get_normal_map() const
{
    return _normalMap;
}

void Material::set_normal_map(Texture normalMap)
{
    _normalMap;
}

Texture Material::get_height_map() const
{
    return _heightMap;
}

void Material::set_height_map(Texture heightMap)
{
    _heightMap = heightMap;
}

Texture Material::get_emission_map() const
{
    return _emissionMap;
}

void Material::set_emission_map(Texture emissionMap)
{
    _emissionMap = emissionMap;
}

float Material::get_metallic() const
{
    return _metallic;
}

void Material::set_metallic(float metallic)
{
    _metallic = metallic;
}

float Material::get_smoothness() const
{
    return _smoothness;
}

void Material::set_smoothness(float smoothness)
{
    _smoothness = smoothness;
}

float Material::get_ao_strength() const
{
    return _aoStrength;
}

void Material::set_ao_strength(float aoStrength)
{
    _aoStrength = aoStrength;
}

bool Material::is_use_alpha_clipping() const
{
    return _useAlphaClipping;
}

void Material::set_use_alpha_clipping(bool useAlphaClipping)
{
    _useAlphaClipping = useAlphaClipping;
}

float Material::get_alpha_clipping_threshold()
{
    return _alphaClippingThreshold;
}

void Material::set_alpha_clipping_threshold(float val)
{
    _alphaClippingThreshold = val;
}

glm::vec4 Material::get_reflect_color() const
{
    return _reflectColor;
}

void Material::set_reflect_color(glm::vec4 newColor)
{
    _reflectColor = newColor;
}

bool Material::is_use_emission_map() const
{
    return _useEmissionMap;
}

void Material::set_use_emission_map(bool use)
{
    _useEmissionMap = use;
}

bool Material::is_use_metallic_map() const
{
    return _useMetallicMap;
}

void Material::set_use_metallic_map(bool use)
{
    _useMetallicMap = use;
}

bool Material::is_received_shadow() const
{
    return _receivedShadow;
}

void Material::set_received_shader(bool use)
{
    _receivedShadow = use;
}

void Material::set_tilling(glm::vec2 newTilling)
{
    _tilling = newTilling;
}

glm::vec2 Material::get_tilling() const
{
    return _tilling;
}

void Material::set_offset(glm::vec2 newOffset)
{
    _offset = newOffset;
}

glm::vec2 Material::get_offset() const
{
    return _offset;
}

SurfaceType Material::get_sufface_type() const
{
    return _surfaceType;
}

void Material::set_sufface_type(SurfaceType newSurfaceType)
{
    _surfaceType = newSurfaceType;
}

RenderFace Material::get_render_face() const
{
    return _renderFace;
}

void Material::set_render_face(RenderFace newRenderFace)
{
    _renderFace = newRenderFace;
}

BlendingMode Material::get_blending_mode() const
{
    return _blendingMode;
}

void Material::set_blending_mode(BlendingMode newBlendingMode)
{
    _blendingMode = newBlendingMode;
}

bool Material::is_use_specular_highlight() const
{
    return _useSpecularHighlight;
}

void Material::set_use_specular_highlight(bool val)
{
    _useSpecularHighlight = val;
}

bool Material::is_use_enviroment_reflections() const
{
    return _useEnviromentReflections;
}

void Material::set_use_enviroment_reflections(bool val)
{
    _useEnviromentReflections = val;
}

bool Material::is_must_update() const
{
    return _mustUpdate;
}

short Material::get_priority_render() const
{
    return _priorityRender;
}

void Material::set_priority_render(short newPriority)
{
    _priorityRender = newPriority;
}
