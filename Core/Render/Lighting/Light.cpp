#include "Light.h"

Light::Light(const Light& base) 
    : Component(base), _specularColor(base._specularColor), _diffuseColor(base._diffuseColor), _index(base._index + 1), _isApplied(false)
{ }

Light::Light(GameObject * owner, bool isActive, glm::vec3 specularColor, glm::vec3 diffuseColor, unsigned int index)
    : Component(owner, "Light", isActive), _specularColor(specularColor), _diffuseColor(diffuseColor), _index(index), _isApplied(false)
{ }

bool Light::isApplied() const
{
    return _isApplied;
}

void Light::set_light_index(unsigned int index)
{
    _index = index;
}

unsigned int Light::get_light_index() const
{
    return _index;
}

void Light::set_diffuse_color(glm::vec3 diffuse)
{
    _diffuseColor = diffuse;
}

glm::vec3 Light::get_diffuse_color() const
{
    return _diffuseColor;
}

void Light::set_specular_color(glm::vec3 specular)
{
    _specularColor = specular;
}

glm::vec3 Light::get_specular_color() const
{
    return _specularColor;
}
