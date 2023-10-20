#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Component.h"

class Component;
class GameObject;

class Transform : public Component {

public:
	Transform(GameObject* gameObject, glm::vec3 position, glm::vec3 scale, glm::quat rotation, bool isActive = true);
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

	glm::vec3	getLocalEulerAngles() const;
	void		setLocalEulerAngles(glm::vec3 eulerAngles);

	glm::vec3	getLocalPosition() const;
	void		setLocalPosition(glm::vec3 newPosition);

	glm::vec3	getLocalScale() const;
	void		setLocalScale(glm::vec3 newScale);

	glm::quat	getLocalRotation() const;
	void		setLocalRotation(glm::quat newRotation);

	/**
	 * Calculate Matrix 4x4 from Transform.
	 * 
	 * \return Matrix 4x4 which descripble transform
	 */
	glm::mat4	getMatrixTransform() const;

	/**
	 * Calculate euler angles from quaternion.
	 * 
	 * \param quaternion: base quaternion
	 * \return Euler angles from quaternion.
	 */
	static glm::vec3 quaternionToEulerAngles(glm::quat& quaternion);
	static glm::quat eulerAnglesToQuaternion(glm::vec3& eulerAngles);
	static glm::quat eulerAnglesToQuaternion(float& pitch, float& yaw, float& roll);

	glm::vec3 getPosition() const;
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getScale() const;
	void setScale(glm::vec3 newScale);
	glm::quat getQuaternion() const;
	void setQuaternion(glm::quat newQuaternion);

	__declspec(property(get = getPosition, put = setPosition)) glm::vec3 position;
	__declspec(property(get = getScale, put = setScale)) glm::vec3 scale;
	__declspec(property(get = getQuaternion, put = setQuaternion)) glm::quat rotation;

private:
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::quat _rotation;
};

#endif
