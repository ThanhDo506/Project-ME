#include "GameObject.h"

GameObject::GameObject(const GameObject& baseGameObject)
	: _active(baseGameObject._active), 
	_name(baseGameObject._name + " (Copy)"), 
	_hasChanged(true),
	_tag(baseGameObject.tag),
	_scene(baseGameObject._scene)
{
	this->set_parent(baseGameObject._parent);
	// TODO add component
	for (auto component : baseGameObject._components) {
		auto copyComp = component.second->Clone();
		copyComp->set_gameObject(this);
#if _DEBUG
		APP_INFO("Add %s", typeid(component.second).name());
#endif
	}
	for (GameObject* child : baseGameObject._children) {
		GameObject* newChild = new GameObject(*child);
		newChild->set_parent(this);
	}
}

GameObject::GameObject(const GameObject& baseGameObject,
	Transform transform, 
	std::string name, 
	GameObject* parent)
	: _name(name), 
	_active(baseGameObject._active)
{

	// TODO add component
	for (auto component : baseGameObject._components) {
		auto copyComp = component.second->Clone();
		copyComp->set_gameObject(this);
#if _DEBUG
		APP_INFO("Add %s", typeid(component.second).name());
#endif
	}
	*this->GetComponent<Transform>() = transform;
	for (GameObject* child : baseGameObject._children) {
		GameObject* newChild = new GameObject(*child);
		newChild->set_parent(this);
	}
	this->set_parent(parent);
}

GameObject::GameObject(Transform transform, 
	std::string name, 
	GameObject* parent,
	bool isActive) 
	: _name(name),
	_active(isActive)
{
	this->AddComponent<Transform>(transform);
	this->set_parent(parent);
}

GameObject::~GameObject()
{
	for (auto component : this->_components) {
		delete component.second;
	}
	this->_components.clear();
	for (GameObject* child : this->_children) {
		delete child;
	}
	this->_children.clear();
}

std::string GameObject::get_name() const {
	return _name;
}

void GameObject::set_name(const std::string newName) {
	this->_name = newName;
}

std::string GameObject::get_tag() const
{
	return this->_tag;
}

void GameObject::set_tag(std::string tag)
{
	this->_tag = tag;
}

bool GameObject::is_active() const {
	return _active;
}

void GameObject::set_active(bool active) {
	this->_active = active;
}

void GameObject::set_parent(GameObject* parent) {
	if (parent == this->_parent) {
		return;
	}
	//* remove from child list of old parent
	if (this->_parent != nullptr) {
		auto it = std::find(this->_parent->_children.begin(), this->_parent->_children.end(), this);
		if (it != this->_parent->_children.end()) {
			this->_parent->_children.erase(it);
			parent->_children.push_back(this);
			this->_parent = parent;
		}
	} else {
		//* set new parent
		this->_parent = parent;
		//* add to child list of new parent if not nullptr
		if (this->_parent) {
			this->_parent->_children.push_back(this);
		}
	}
}

GameObject* GameObject::get_parent() {
	return _parent;
}

GameObject* GameObject::FindInChild(std::string name)
{
	if (this->_name == name)
	{
		return this;
	}
	for (GameObject* child : this->_children)
	{
		GameObject* res = child->FindInChild(name);
		if (res != nullptr)
		{
			return res;
		}
	}
	return nullptr;
}

bool GameObject::IsChildOf(const GameObject* gameObject) const 
{
	if (this->_parent == nullptr) {
		return gameObject == nullptr;
	}
	bool check1 = (gameObject == _parent);
	bool check2 = (std::find(_parent->_children.begin(), _parent->_children.end(), gameObject) != _parent->_children.end());
	if (check1 && !check2) {
		APP_WARN("%s 's parent is &s, but isn't assigned in _children of &s list! Please fix it.");
	}
	else if (check2 && !check1) {
		APP_WARN("%s assigned in _children of %s list, but %s parent is not %s! Please fix it.");
	}
	return (check1 && check2);
}

void GameObject::RemoveChild(GameObject* instance)
{
	if (instance->IsChildOf(this)) {
		std::vector<GameObject*>::iterator it = std::find(_parent->_children.begin(), _parent->_children.end(), instance);
		GameObject* erasedObject = *it;
		_children.erase(it);
		delete erasedObject;
	}
}

Scene* GameObject::get_scene()
{
	return this->_scene;
}

void GameObject::OnEnable() 
{
	for (auto component : _components) {
		component.second->OnEnable();
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
	for (auto component : _components) {
		component.second->OnDisable();
	}
}

void GameObject::Awake() 
{
	for (auto component : _components) {
		component.second->Awake();
	}
	for (GameObject* child : _children) {
		child->Awake();
	}
}

void GameObject::Start() 
{
	for (auto component : _components) {
		component.second->Start();
	}
}

void GameObject::Update() 
{
	if (!_active)
		return;
	for (auto component : _components) {
		if (component.second->is_active()) {
			component.second->Update();
		}
	}
	for (GameObject* child : _children) {
		child->Update();
	}
}

void GameObject::Destroy(GameObject* instance, float time)
{
	//this->_scene->Destroy(instance, time);
}

void GameObject::Destroy(Component* component, float time)
{
}
