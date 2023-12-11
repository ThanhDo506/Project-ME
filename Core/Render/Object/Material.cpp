#include "Material.h"

Texture* Material::get_diffuse_map() 
{
    return this->_diffuseMap;
}

void Material::set_diffuse_map(Texture* diffuseMap)
{
    _textureChanged = true;
    _diffuseMap = diffuseMap;
}

Texture* Material::get_roughness_map()
{
    return this->_roughnessMap;
}

void Material::set_roughness_map(Texture* roughnessMap)
{
    _textureChanged = true;
    _roughnessMap = roughnessMap;
}

Texture* Material::get_metallic_map()
{
    return this->_metallicMap;
}

void Material::set_metallic_map(Texture* metallicMap)
{
    _textureChanged = true;
    _metallicMap = metallicMap;
}

Texture* Material::get_ao_map()
{
    return this->_aoMap;
}

void Material::set_ao_map(Texture* aoMap)
{
    _textureChanged = true;
    _aoMap = aoMap;
}

Texture* Material::get_normal_map()
{
    return this->_normalMap;
}

void Material::set_normal_map(Texture* normalMap)
{
    _textureChanged = true;
    _normalMap = normalMap;
}

Texture* Material::get_height_map()
{
    return this->_heightMap;
}

void Material::set_height_map(Texture* heightMap)
{
    _textureChanged = true;
    _heightMap = heightMap;
}

Texture* Material::get_emission_map()
{
    return this->_emissionMap;
}

void Material::set_emission_map(Texture* emissionMap)
{
    _textureChanged = true;
    _emissionMap = emissionMap;
}

float Material::get_metallic() const
{
    return _metallic;
}

void Material::set_metallic(float metallic)
{
    _mustUpdate = true;
    _metallic = metallic;
}

float Material::get_smoothness() const
{
    return _smoothness;
}

void Material::set_smoothness(float smoothness)
{
    _mustUpdate = true;
    _smoothness = smoothness;
}

float Material::get_ao_strength() const
{
    return _aoStrength;
}

void Material::set_ao_strength(float aoStrength)
{
    _mustUpdate = true;
    _aoStrength = aoStrength;
}

bool Material::is_use_alpha_clipping() const
{
    return _useAlphaClipping;
}

void Material::set_use_alpha_clipping(bool useAlphaClipping)
{
    _mustUpdate = true;
    _useAlphaClipping = useAlphaClipping;
}

float Material::get_alpha_clipping_threshold()
{
    return _alphaClippingThreshold;
}

void Material::set_alpha_clipping_threshold(float val)
{
    _mustUpdate = true;
    _alphaClippingThreshold = val;
}

glm::vec4 Material::get_base_color() const
{
    return _baseColor;
}

void Material::set_base_color(glm::vec4 newColor)
{
    _mustUpdate = true;
    _baseColor = newColor;
}

bool Material::is_use_emission_map() const
{
    return _useEmissionMap;
}

void Material::set_use_emission_map(bool use)
{
    _mustUpdate = true;
    _useEmissionMap = use;
}

bool Material::is_use_metallic_map() const
{
    return _useMetallicMap;
}

void Material::set_use_metallic_map(bool use)
{
    _mustUpdate = true;
    _useMetallicMap = use;
}

bool Material::is_received_shadow() const
{
    return _receivedShadow;
}

void Material::set_received_shader(bool use)
{
    _mustUpdate = true;
    _receivedShadow = use;
}

void Material::set_tilling(glm::vec2 newTilling)
{
    _textureChanged = true;
    _tilling = newTilling;
}

glm::vec2 Material::get_tilling() const
{
    return _tilling;
}

void Material::set_offset(glm::vec2 newOffset)
{
    _textureChanged = true;
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
    _mustUpdate = true;
    _surfaceType = newSurfaceType;
}

RenderFace Material::get_render_face() const
{
    return _renderFace;
}

void Material::set_render_face(RenderFace newRenderFace)
{
    _mustUpdate = true;
    _renderFace = newRenderFace;
}

BlendingMode Material::get_blending_mode() const
{
    return _blendingMode;
}

void Material::set_blending_mode(BlendingMode newBlendingMode)
{
    _mustUpdate = true;
    _blendingMode = newBlendingMode;
}

bool Material::is_use_specular_highlight() const
{
    return _useSpecularHighlight;
}

void Material::set_use_specular_highlight(bool val)
{
    _mustUpdate = true;
    _useSpecularHighlight = val;
}

bool Material::is_use_enviroment_reflections() const
{
    return _useEnviromentReflections;
}

void Material::set_use_enviroment_reflections(bool val)
{
    _mustUpdate = true;
    _useEnviromentReflections = val;
}

bool Material::is_must_update() const
{
    return _mustUpdate;
}

bool Material::is_texture_changed() const
{
    return _textureChanged;
}

short Material::get_priority_render() const
{
    return _priorityRender;
}

void Material::set_priority_render(short newPriority)
{
    _priorityRender = newPriority;
}

Shader& Material::get_shader()
{
    return this->_shader;
}

void Material::set_shader(const Shader& shader)
{
    this->_shader = shader;
}
