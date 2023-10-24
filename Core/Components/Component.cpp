#include "Component.h"

Component::~Component()
{
	_gameObject = nullptr;
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
