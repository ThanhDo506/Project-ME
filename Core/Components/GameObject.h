#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <vector>
#include "Transform.h"
#include "IComponent.h"
#include "../common.h"
#include <algorithm>

class GameObject {

private:
	bool						_active;
	bool						_hasChanged;
	int							_childCount;
	Transform					transform;
	std::string					name;
	std::string					tag;
	std::list<GameObject*>		_children;
	GameObject*					parent;
	std::vector<IComponent*>	_components;

public:
	GameObject(Transform& transform,const char* name = "Game Object", GameObject* parent = nullptr);

	std::string getName() const;

	void setName(std::string& newName);

	bool isActive() const;

	void setActive(bool active);

	void setParent(GameObject* parent);

	GameObject* getParent();

	void setTransform(Transform& newTransform);

	Transform getTransform() const;

	bool isChildOf(GameObject& gameObject) const;

	void Destroy(GameObject& gameObject, float time = 0.0f);

	virtual void OnEnable();

	virtual void OnDisable();

	virtual void Awake();

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	template<typename T>
	T* GetComponent() const {
		for (IComponent* component : _components) {
			if (dynamic_cast<T*>(component) != nullptr) {
				return static_cast<T*>(component);
			}
		}
		return nullptr;
	}

	template<typename T>
	void AddComponent(T* component) {
		_components.push_back(component);
	}

	template<typename T>
	bool RemoveComponent(T* component) {
		std::vector<IComponent*>::iterator it = std::find(_components.begin(), _components.end(), component);
		_components.erase(it);
	}
};

#endif
