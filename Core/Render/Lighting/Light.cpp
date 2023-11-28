#include "Light.h"

Light::Light() 
	: Component(nullptr)
	, _isMustUpdate(true)
{
	Rendering::add_light_to_registry(this);
}

Light::Light(GameObject* gameObject, bool isActive)
	: Component(gameObject, isActive)
	, _isMustUpdate(true)
{
	Rendering::add_light_to_registry(this);
}

Light::~Light()
{
	Rendering::remove_light_from_registry(this);
}

bool Light::is_must_update() const
{
	return this->_isMustUpdate;
}

glm::vec3 Light::get_color() const
{
	return _color;
}

void Light::set_color(glm::vec3 color)
{
	_isMustUpdate = true;
	this->_color = color;
}

glm::vec3 Light::get_ambient() const
{
	return _ambient;
}

void Light::set_ambient(glm::vec3 color)
{
	_isMustUpdate = true;
	_ambient = color;
}

glm::vec3 Light::get_diffuse() const
{
	return _diffuse;
}

void Light::set_diffuse(glm::vec3 color)
{
	_isMustUpdate = true;
	_diffuse = color;
}

glm::vec3 Light::get_specular() const
{
	return _specular;
}

void Light::set_specular(glm::vec3 color)
{
	_isMustUpdate = true;
	_specular = color;
}

glm::vec3 Light::get_spot_angle() const
{
	return _spotAngle;
}

void Light::set_spot_angle(glm::vec3 angle)
{
	_isMustUpdate = true;
	_spotAngle = angle;
}

glm::vec3 Light::get_inner_angle() const
{
	return _innerSpotAngle;
}

void Light::set_inner_angle(glm::vec3 angle)
{
	_isMustUpdate = true;
	_innerSpotAngle = angle;
}

float Light::get_range() const
{
	return _range;
}

void Light::set_range(float range)
{
	_isMustUpdate = true;
	_range = range;
}

float Light::get_intensity() const
{
	return _intensity;
}

void Light::set_intensity(float range)
{
	_isMustUpdate = true;
	_intensity = range;
}

LightType Light::get_light_type() const
{
	return _lightType;
}

void Light::set_light_type(LightType type)
{
	_isMustUpdate = true;
	_lightType = type;
}

