#include "Light.h"

bool Light::isApplied() const
{
    return _isApplied;
}

void Light::setApplied(bool applied)
{
    _isApplied = applied;
}

glm::vec3 Light::getLightColor() const
{
    return _lightColor;
}

void Light::setLightColor(glm::vec3 newColor)
{
    _lightColor = newColor;
}

glm::vec3 Light::getRenderColor() const
{
    return _lightColor * _intensity;
}

void Light::setLightIndex(unsigned int index)
{
    _index = index;
}

void Light::getLightIndex() const
{
}
