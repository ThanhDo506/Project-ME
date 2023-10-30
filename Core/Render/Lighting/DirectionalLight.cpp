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

Light::LightType DirectionalLight::get_light_type() const
{
    return Light::DirectionalLight;
}

std::string DirectionalLight::get_uniform_name() const
{
    return _uniformName;
}

void DirectionalLight::UpdateShader(Shader& shader)
{
    if (_isApplied || !_isUpdated)
        return;
    shader.SetVec3(_uniformName + ".direction", _gameObject->transform->forward());
    shader.SetVec3(_uniformName + ".diffuse", _diffuseColor);
    shader.SetVec3(_uniformName + ".specular", _specularColor);
    _isUpdated = true;
}
