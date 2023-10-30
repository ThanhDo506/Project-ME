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
	friend class Component;
	friend class Scene;
public:
	GameObject(const GameObject& baseGameObject);
	GameObject(const GameObject& baseGameObject, const Transform& transform, std::string name = "Game Object", GameObject* parent = nullptr);
	GameObject(const Transform& transform, std::string = "Game Object", GameObject* parent = nullptr);

	void set_parent(GameObject* parent);

	GameObject* get_parent();

	Transform* get_transform();

	void set_transform(const Transform& tranform);

	GameObject* findInChild(std::string name);

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

	// just call new Component, it'll auto fixed owner
	void AddComponent(Component* component);

	std::string get_name() const;

	void set_name(const std::string newName);

	bool isActive() const;

	void setActive(bool active);

	GameObject* Clone() const;

	__declspec(property(get = get_parent	, put = set_parent))	GameObject* parent;
	__declspec(property(get = get_name		, put = set_name))		std::string name;
	__declspec(property(get = get_transform	, put = set_transform))	Transform*	transform;
	__declspec(property(get = getTag		, put = setTag))		std::string tag;
	std::vector<Component*>		_components;

private:
	bool						_active;
	bool						_hasChanged = true;
	std::string					_name;
	std::string					_tag;
	GameObject*					_parent;
	std::vector<GameObject*>	_children;
	Transform					_transform;

};

#endif
