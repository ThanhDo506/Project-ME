#include "Component.h"

Component::Component(const Component& base)
	: _gameObject(base._gameObject), _active(base._active)
{
}

Component::Component(const Component& base, GameObject* owner)
	: _gameObject(owner), _active(base._active)
{
}

Component::Component(GameObject* owner, bool isActive) 
	: _gameObject(owner), _active(isActive)
{
}

Component::~Component()
{
	this->_gameObject = nullptr;
}

void Component::Awake()
{
}

void Component::Start()
{
}

void Component::Update()
{
}

void Component::OnDestroy()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::set_active(bool active) 
{
	_active = active;
}

bool Component::is_active() const 
{
	return _active;
}

GameObject* Component::get_gameObject()
{
	return _gameObject;
}

std::string Component::to_string() const
{
	return typeid(this).name();
}

void Component::set_gameObject(GameObject* gameObject)
{
	if (this->_gameObject != nullptr) {
		auto it = this->_gameObject->_components.find(typeid(this));
		if (it != this->_gameObject->_components.end()) {
			this->_gameObject->_components.erase(it);
		}
	}
	else {
		APP_ERROR("Must attach component to a valid GameObject!");
	}
	this->_gameObject = gameObject;
	this->_gameObject->_components.insert({typeid(this), this});
}


Transform::Transform()
	: Component(nullptr, true),
	_position(glm::vec3(0.0, 0.0, 0.0)),
	_scale(glm::vec3(1.0, 1.0, 1.0)),
	_rotation(glm::quat(0.0, 0.0, 0.0, 0.0)) { }

Transform::Transform(const Transform& base)
	: Component(nullptr, true),
	_position(base._position),
	_scale(base._scale),
	_rotation(base._rotation) { }

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation)
	: Component(nullptr, true),
	_position(position),
	_scale(scale),
	_rotation(rotation) { }

glm::vec3 Transform::up() const {
	return _rotation * glm::vec3(0.0, 1.0, 0.0);
}

glm::vec3 Transform::forward() const {
	return glm::normalize(_rotation * glm::vec3(0.0, 0.0, 1.0));
}

glm::vec3 Transform::right() const {
	return _rotation * glm::vec3(1.0, 0.0, 0.0);
}

glm::vec3 Transform::get_local_euler_angles() const
{
	return glm::degrees(glm::eulerAngles(_rotation));
}

void Transform::set_local_euler_angles(glm::vec3 eulerAngles)
{
	_rotation = glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::vec3 Transform::get_local_position() const
{
	return _position;
}

void Transform::set_local_position(glm::vec3 newPosition)
{
	_position = newPosition;
}

glm::vec3 Transform::get_local_scale() const
{
	return _scale;
}

void Transform::set_local_scale(glm::vec3 newScale)
{
	_scale = newScale;
}

glm::quat Transform::get_local_rotation() const
{
	return _rotation;
}

void Transform::set_local_rotation(glm::quat newRotation)
{
	_rotation = newRotation;
}

glm::mat4 Transform::get_matrix_transform() const
{
	glm::mat4 positionMtx = glm::translate(glm::mat4(1.0), _position);
	glm::mat4 scaleMtx = glm::scale(glm::mat4(1.0), _scale);
	glm::mat4 rotationMtx = glm::toMat4(_rotation);
	return positionMtx * rotationMtx * scaleMtx;
}

glm::vec3 Transform::quaternion_to_euler_angles(glm::quat& quaternion)
{
	return glm::eulerAngles(quaternion);
}

glm::quat Transform::euler_angles_to_quaternion(glm::vec3& eulerAngles)
{
	return glm::quat(glm::vec3(
		glm::radians(eulerAngles.x),
		glm::radians(eulerAngles.y),
		glm::radians(eulerAngles.z)
	));
}

glm::quat Transform::euler_angles_to_quaternion(float& pitch, float& yaw, float& roll)
{
	return glm::quat(glm::vec3(
		glm::radians(pitch),
		glm::radians(yaw),
		glm::radians(roll)
	));
}

glm::vec3 Transform::get_position() const
{
	return _position;
}

void Transform::set_position(glm::vec3 newPosition)
{
	_position = newPosition;
}

glm::vec3 Transform::get_scale() const
{
	return _scale;
}

void Transform::set_scale(glm::vec3 newScale)
{
	_scale = newScale;
}

glm::quat Transform::get_rotation() const
{
	return _rotation;
}

void Transform::set_rotation(glm::quat newRotation)
{
	_rotation = newRotation;
}

