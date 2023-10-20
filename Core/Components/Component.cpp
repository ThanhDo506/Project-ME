#include "Component.h"

// TODO: 
Component::Component(GameObject* gameObject, std::string name, bool isActive)
{
	APP_CRITICAL("Create Component with null gameObject!");
	assert(gameObject == nullptr);
	_gameObject	= gameObject;
	_name		= name;
	_active		= isActive;
}

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