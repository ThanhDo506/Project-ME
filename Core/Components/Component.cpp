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

std::string Component::getName() const 
{
	return _name;
}

void Component::setName(std::string name)
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

GameObject* Component::getGameObject()
{
	return _gameObject;
}

Component::Component(const Component& obj, GameObject* gameObject)
{

}

void Component::operator=(const Component& obj)
{

}
