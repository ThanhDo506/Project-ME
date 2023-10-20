#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <vector>
#include "Transform.h"
#include "Component.h"
#include "../common.h"
#include <algorithm>

class Component;

class GameObject {
public:
	GameObject(GameObject& baseGameObject);
	GameObject(Transform transform, const char* name = "Game Object", GameObject* parent = nullptr);

	void setParent(GameObject* parent);

	GameObject* getParent();

	Transform* getTransform() const;

	void setTransform(Transform tranform);

	bool isChildOf(GameObject& gameObject) const;

	virtual void OnEnable();

	virtual void OnDisable();

	virtual void Awake();

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	template<typename T>
	T* GetComponent() const {
		for (Component* component : _components) {
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

	bool RemoveComponent(Component* component) {
		std::vector<Component*>::iterator it = std::find(_components.begin(), _components.end(), component);
		_components.erase(it);
	}

	std::string getName() const;

	void setName(std::string& newName);

	bool isActive() const;

	void setActive(bool active);


	__declspec(property(get = getName		, put = setName))		std::string name;
	__declspec(property(get = getTransform	, put = setTransform))	Transform*	transform;
	__declspec(property(get = getTag		, put = setTag))		std::string tag;
private:
	bool						_active;
	bool						_hasChanged;
	std::string					_name;
	std::string					_tag;
	GameObject* _parent;
	std::vector<GameObject*>	_children;
	std::vector<Component*>		_components;
};

#endif
