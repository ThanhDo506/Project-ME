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

    void set_active(bool val);

	bool is_active() const;

	GameObject* get_gameObject();

	//template <typename T, typename... Args>
	//T* AddComponent(Args&&... args) {
	//	return this->_gameObject->AddComponent<T>(args);
	//}

	//template <typename T>
	//bool HasComponent() {
	//	return this->_gameObject->HasComponent<T>();
	//}

	//template<typename T>
	//T* GetComponent() {
	//	return this->_gameObject->GetComponent<T>();
	//}

	//template<typename T>
	//void RemoveComponent() {
	//	this->_gameObject->RemoveComponent<T>();
	//}
	virtual std::string to_string() const;

	__declspec(property(get = get_gameObject))				GameObject* gameObject;

protected:
	bool		_active;
	GameObject* _gameObject;

	void set_gameObject(GameObject* gameObject);
};

class Transform : public Component {
public:
	Transform();

	Transform(const Transform& base);

	Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);

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

	glm::vec3	get_local_euler_angles() const;
	void		set_local_euler_angles(glm::vec3 eulerAngles);
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
	static glm::vec3 quaternion_to_euler_angles(glm::quat& quaternion);
	static glm::quat euler_angles_to_quaternion(glm::vec3& eulerAngles);
	static glm::quat euler_angles_to_quaternion(float& pitch, float& yaw, float& roll);

	glm::vec3	get_position() const;
	void		set_position(glm::vec3 newPosition);
	glm::vec3	get_scale() const;
	void		set_scale(glm::vec3 newScale);
	glm::quat	get_rotation() const;
	void		set_rotation(glm::quat newQuaternion);

	Transform* Clone() const override {
		return new Transform(*this);
	}

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
