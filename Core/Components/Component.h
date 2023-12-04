#ifndef COMPONENT_H
#define COMPONENT_H

#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <string>
#include "../common.h"
#include "GameObject.h"

class GameObject;

class Component {
	friend class GUI;
	friend class GameObject;
public:
	Component(const Component& base);

	Component(const Component& base, GameObject* owner);

	Component(GameObject* owner, bool isActive = true);

	virtual Component* Clone() const = 0;

	virtual ~Component();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void OnDestroy();
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnGui() = 0;

    void set_active(bool val);

	bool is_active() const;

	GameObject* get_gameObject();
	void set_gameObject(GameObject* gameObject);
	void attach_to_gameObject(GameObject* gameObject);

	virtual std::string to_string() const;

	__declspec(property(get = get_gameObject))				GameObject* gameObject;
protected:
	bool		_active;
	GameObject* _gameObject;
};

class Transform : public Component {
public:
	Transform();

	Transform(const Transform& base);

	Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);

	Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 eulerAngle);

	/**
	 * @return The green axis of the transform in world space.
	 */
	glm::vec3	up() const;

	/**
	 * @return A normalized vector representing the blue axis of the transform in world
	 * space.
	 */
	glm::vec3	forward() const;

	/**
	 * @return The red axis of the transform in world space.
	 */
	glm::vec3	right() const;

	glm::vec3	get_local_euler_angles() const;
	void		set_local_euler_angles(glm::vec3 eulerAngles);
	// Todo: should optimize this func :(((
	glm::vec3	get_world_euler_angles() const;
	void		set_world_euler_angles(glm::vec3 eulerAngles);

	glm::vec3	get_local_position() const;
	void		set_local_position(glm::vec3 position);
	glm::vec3	get_world_position() const;
	void		set_world_position(glm::vec3 position);

	glm::vec3	get_local_scale() const;
	void		set_local_scale(glm::vec3 scale);
	glm::vec3	get_world_scale() const;
	void		set_world_scale(glm::vec3 scale);

	glm::quat	get_local_rotation() const;
	void		set_local_rotation(glm::quat rotation);
	glm::vec3	get_world_rotation() const;
	void		set_world_rotation(glm::quat rotation);


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
	static glm::vec3 quaternion_to_euler_angles(const glm::quat& quaternion);
	static glm::quat euler_angles_to_quaternion(const glm::vec3& eulerAngles);
	static glm::quat euler_angles_to_quaternion(const float& pitch, const float& yaw, const float& roll);

	glm::vec3	get_position() const;
	void		set_position(glm::vec3 newPosition);
	glm::vec3	get_scale() const;
	void		set_scale(glm::vec3 newScale);
	glm::quat	get_rotation() const;
	void		set_rotation(glm::quat newQuaternion);

	Transform* Clone() const override {
		return new Transform(*this);
	}

	void OnGui() override;

	std::string to_string() const override { return "Transform"; }

	__declspec(property(get = get_position, put = set_position)) glm::vec3 position;
	__declspec(property(get = get_scale, put = set_scale)) glm::vec3 scale;
	__declspec(property(get = get_rotation, put = set_rotation)) glm::quat rotation;

private:
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::quat _rotation;
};

#endif
