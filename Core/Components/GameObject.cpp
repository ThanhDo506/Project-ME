#include "GameObject.h"

GameObject::GameObject(GameObject& baseGameObject)
{
	_active = baseGameObject._active;
	_hasChanged = true;
	_name = baseGameObject.name + " (Copy)";
	_parent = baseGameObject._parent;
	_children = baseGameObject._children;
}

GameObject::GameObject(Transform transform,const char* name, GameObject* parent) {
	Transform* t = new Transform(transform);
	this->AddComponent(t);
	this->_name = name;
	this->_parent = parent;
}

std::string GameObject::get_name() const {
	return _name;
}

void GameObject::set_name(std::string& newName) {
	this->_name = newName;
}

bool GameObject::isActive() const {
	return _active;
}

void GameObject::setActive(bool active) {
	this->_active = active;
}

void GameObject::setParent(GameObject* parent) {
	this->_parent = parent;
}

GameObject* GameObject::getParent() {
	return this->_parent;
}

Transform* GameObject::getTransform() const
{
	return GetComponent<Transform>();
}

void GameObject::setTransform(Transform tranform)
{
	Transform* trans = GetComponent<Transform>();
	*trans = tranform;
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
