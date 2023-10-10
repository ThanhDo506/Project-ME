#include "IComponent.h"

void IComponent::Awake() {
}

void IComponent::Start() {
}

void IComponent::Update() {
}

void IComponent::FixedUpdate() {
}

void IComponent::OnDestroy() {
}

void IComponent::OnEnable() {

}

void IComponent::OnDisable() {

}

std::string IComponent::getName() const {
	return _name;
}

void IComponent::setName(const char* name) {
	_name = std::string(name);
}

void IComponent::setActive(bool active) {
	_active = active;
}

bool IComponent::isActive() const {
	return _active;
}
