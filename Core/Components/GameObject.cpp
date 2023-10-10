#include "GameObject.h"

GameObject::GameObject(Transform& transform,const char* name, GameObject* parent) {
	this->transform = transform;
	this->name = name;
	this->parent = parent;
}

std::string GameObject::getName() const {
	return name;
}

void GameObject::setName(std::string& newName) {
	this->name = newName;
}

bool GameObject::isActive() const {
	return active;
}

void GameObject::setActive(bool active) {
	this->active = active;
}

void GameObject::setParent(GameObject* parent) {
	this->parent = parent;
}

GameObject* GameObject::getParent() {
	return this->parent;
}

void GameObject::setTransform(Transform& newTransform) {
	this->transform = newTransform;
}

Transform GameObject::getTransform() const {
	return this->transform;
}

bool GameObject::isChildOf(GameObject& gameObject) const {
	return (& gameObject == parent);
}

void GameObject::Destroy(GameObject& gameObject, float time) {
}

void GameObject::OnEnable() {
}

void GameObject::OnDisable() {
}

void GameObject::Awake() {
}

void GameObject::Start() {
}

void GameObject::Update() {
}

void GameObject::FixedUpdate() {
}
