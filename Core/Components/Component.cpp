#include "Component.h"

Component::Component(const Component& base)
{
	_name = base._name;
	_active = base._active;
	_gameObject = base._gameObject;
}

Component::Component(const Component& base, GameObject* owner)
{
	_name = base._name;
	_active = base._active;
	_gameObject = owner;
}

Component::Component(GameObject* owner, std::string name, bool isActive) 
	: _gameObject(owner), _name(name), _active(isActive)
{
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

void Component::FixedUpdate()
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

std::string Component::get_name() const 
{
	return _name;
}

void Component::set_name(std::string name)
{
	_name = name;
}

void Component::setActive(bool active) 
{
	_active = active;
}

bool Component::isActive() const 
{
	return _active;
}

GameObject* Component::get_gameObject()
{
	return _gameObject;
}

Transform* Component::get_gameObject_transform()
{
	return _gameObject->transform;
}

void Component::set_gameObject_transform(const Transform& newTransform)
{
	*(_gameObject->transform) = newTransform;
}

void Component::set_owner(GameObject* gameObject)
{
	_gameObject = gameObject;
}
