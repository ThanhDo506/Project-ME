#ifndef LIGHT_H
#define LIGHT_H

#include "../../Components/Component.h"
#include "../Object/Shader.h"
#include "../RenderingSystem/Rendering.h"

enum class LightType {
	Directional,
	Spot,
	Point
};

class Light : public Component
{	
	friend class LightRegistry;
public:
	Light();
	Light(GameObject* gameObject, bool isActive = true);
	~Light();

	bool		is_must_update() const;

	glm::vec3	get_color() const;
	void		set_color(glm::vec3 color);

	glm::vec3	get_ambient() const;
	void		set_ambient(glm::vec3 color);

	glm::vec3	get_diffuse() const;
	void		set_diffuse(glm::vec3 color);

	glm::vec3	get_specular() const;
	void		set_specular(glm::vec3 color);

	glm::vec3	get_spot_angle() const;
	void		set_spot_angle(glm::vec3 angle);

	glm::vec3	get_inner_angle() const;
	void		set_inner_angle(glm::vec3 angle);

	float		get_range() const;
	void		set_range(float range);

	float		get_intensity() const;
	void		set_intensity(float range);

	LightType	get_light_type() const;
	void		set_light_type(LightType type);

	Light* Clone() const override;

	std::string to_string() const;

	__declspec(property(get = get_color,
						put = set_color))			glm::vec3 color;
	__declspec(property(get = get_ambient,
						put = set_ambient))			glm::vec3 ambient;
	__declspec(property(get = get_diffuse,
						put = set_diffuse))			glm::vec3 diffuse;
	__declspec(property(get = get_specular,
						put = set_specular))		glm::vec3 specular;
	__declspec(property(get = get_spot_angle,
						put = set_spot_angle))		glm::vec3 spotAngle;
	__declspec(property(get = get_inner_angle,
						put = set_inner_angle))		glm::vec3 innerSpotAngle;
	__declspec(property(get = get_range,
						put = set_range))			float range;
	__declspec(property(get = get_intensity,
						put = set_intensity))		float intensity;
	__declspec(property(get = get_light_type,
						put = set_light_type))		LightType lightType;

private:
	glm::vec3	_color			= glm::vec3(1.0);
	glm::vec3	_ambient		= glm::vec3(1.0);
	glm::vec3	_diffuse		= glm::vec3(0.0);
	glm::vec3	_specular		= glm::vec3(0.0);
	glm::vec3	_spotAngle		= glm::vec3(0.0);
	glm::vec3	_innerSpotAngle = glm::vec3(1.0);
	float		_range			= 10.0;
	float		_intensity		= 1.0;
	LightType	_lightType		= LightType::Point;
	bool		_isMustUpdate	= true;
};

#endif