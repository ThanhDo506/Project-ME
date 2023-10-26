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
	if (_gameObject == nullptr) {
		APP_WARN("Component %s (Address: %p)  attach to null GameObject!", _name.c_str(), this);
	}
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

void Component::set_gameObject(GameObject* gameObject)
{
	_gameObject = gameObject;
}
