#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Component.h"

class Transform : public Component {

public:
	Transform(GameObject* gameObject, glm::vec3 position, glm::vec3 scale, glm::quat rotation, bool isActive = true) : Component(gameObject, "Transform", true)
	{
		_position = position;
		_scale = scale;
		_rotation = rotation;
	}
	Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation, bool isActive = true) : Component(nullptr, "Transform", true)
	{
		_position = position;
		_scale = scale;
		_rotation = rotation;
	}
	/**
	 * @brief The green axis of the transform in world space.
	 */
	glm::vec3	up() const;

	/**
	 * @brief Returns a normalized vector representing the blue axis of the transform in world
     * space.
	 */
	glm::vec3	forward() const;

	/**
	 * @brief The red axis of the transform in world space.
	 */
	glm::vec3	right() const;

	glm::vec3	get_local_eulerAngles() const;
	void		set_local_eulerAngles(glm::vec3 eulerAngles);

	glm::vec3	get_local_position() const;
	void		set_local_position(glm::vec3 newPosition);

	glm::vec3	get_local_scale() const;
	void		set_local_scale(glm::vec3 newScale);

	glm::quat	get_local_rotation() const;
	void		set_local_rotation(glm::quat newRotation);

	/**
	 * Calculate Matrix 4x4 from Transform.
	 * @param
	 * \return Matrix 4x4 which descripble transform
	 */
	glm::mat4	get_matrix_transform() const;

	/**
	 * Calculate euler angles from quaternion.
	 * 
	 * \param quaternion: base quaternion
	 * \return Euler angles from quaternion.
	 */
	static glm::vec3 quaternion_to_eulerAngles(glm::quat& quaternion);
	static glm::quat eulerAngles_to_quaternion(glm::vec3& eulerAngles);
	static glm::quat eulerAngles_to_quaternion(float& pitch, float& yaw, float& roll);

	glm::vec3	get_position() const;
	void		set_position(glm::vec3 newPosition);
	glm::vec3	get_scale() const;
	void		set_scale(glm::vec3 newScale);
	glm::quat	get_rotation() const;
	void		set_rotation(glm::quat newQuaternion);

	__declspec(property(get = get_position, put = set_position)) glm::vec3 position;
	__declspec(property(get = get_scale, put = set_scale)) glm::vec3 scale;
	__declspec(property(get = get_rotation, put = set_rotation)) glm::quat rotation;

private:
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::quat _rotation;
};

#endif
