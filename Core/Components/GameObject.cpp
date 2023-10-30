#include "GameObject.h"

GameObject::GameObject(const GameObject& baseGameObject)
{
	_active		= baseGameObject._active;
	_name		= baseGameObject._name + " (Copy)";
	_parent		= baseGameObject._parent;
	_transform	= baseGameObject._transform;
	for (auto component : _components) {
		this->AddComponent(component->Clone(this));
	}
}

GameObject::GameObject(const GameObject& baseGameObject, const Transform& transform, std::string name, GameObject* parent)
	:	_transform(transform), _name(name), _parent(parent)
{
	for (auto component : _components) {
		this->AddComponent(component->Clone(this));
	}
}

GameObject::GameObject(const Transform& transform, std::string name, GameObject* parent) {
	this->_name = name;
	this->_parent = parent;
	_transform = transform;
	for (auto component : _components) {
		this->AddComponent(component->Clone(this));
	}
}

void GameObject::AddComponent(Component* component)
{
	APP_INFO("Add component %s (Address %p) to %s object.", component->_name.c_str(), component, this->_name.c_str());
	_components.push_back(component);
	component->_gameObject = this;
}

std::string GameObject::get_name() const {
	return _name;
}

void GameObject::set_name(const std::string newName) {
	this->_name = newName;
}

bool GameObject::isActive() const {
	return _active;
}

void GameObject::setActive(bool active) {
	this->_active = active;
}

GameObject* GameObject::Clone() const
{
	GameObject* clone = new GameObject(*this);
	clone->_name = this->_name + " (Copy)";
	for (auto child : _children) {
		GameObject* newChild = child->Clone();
		newChild->_parent = clone;
	}
	return clone;
}

void GameObject::set_parent(GameObject* parent) {
	_parent = parent;
}

GameObject* GameObject::get_parent() {
	return _parent;
}

Transform* GameObject::get_transform()
{
	return &_transform;
}

void GameObject::set_transform(const Transform& tranform)
{
	_transform = tranform;
}

GameObject* GameObject::findInChild(std::string name)
{
	if (this->_name == name)
	{
		return this;
	}
	for (GameObject* child : this->_children)
	{
		GameObject* res = child->findInChild(name);
		if (res != nullptr)
		{
			return res;
		}
	}
	return nullptr;
}

bool GameObject::isChildOf(GameObject& gameObject) const 
{
	return (&gameObject == _parent);
}

void GameObject::OnEnable() 
{
	for (Component* component : _components) {
		component->OnEnable();
	}
	for (GameObject* child : _children) {
		child->OnEnable();
	}
}

void GameObject::OnDisable() 
{
	for (GameObject* child : _children) {
		child->OnDisable();
	}
	for (Component* component : _components) {
		component->OnDisable();
	}
}

void GameObject::Awake() 
{
	for (Component* component : _components) {
		component->Awake();
	}
	for (GameObject* child : _children) {
		child->Awake();
	}
}

void GameObject::Start() 
{
	for (Component* component : _components) {
		component->Start();
	}
}

void GameObject::Update() 
{
	if (!_active)
		return;
	for (Component* component : _components) {
		if (component->isActive()) {
			component->Update();
		}
	}
	for (GameObject* child : _children) {
		child->Update();
	}
}

void GameObject::FixedUpdate() 
{
	if (!_active)
		return;
	for (Component* component : _components) {
		if (component->isActive()) {
			component->FixedUpdate();
		}
	}
	for (GameObject* child : _children) {
		child->FixedUpdate();
	}
}
