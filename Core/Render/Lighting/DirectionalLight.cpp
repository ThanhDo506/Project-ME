#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const DirectionalLight& base, GameObject* owner)
    : Light(owner, "Directional Light", true, base.index + 1, base._specularColor, base._diffuseColor)
{
}

DirectionalLight::DirectionalLight(GameObject* owner, unsigned int index, 
    glm::vec3 direction, glm::vec3 specularColor, glm::vec3 diffuseColor)
    : Light(owner, "Directional Light", true, index , specularColor, diffuseColor)
{
}

glm::vec3 DirectionalLight::get_direction() const
{
    return _gameObject->transform->forward();
}
