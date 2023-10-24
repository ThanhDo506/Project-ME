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
	GameObject(Transform transform, std::string = "Game Object", GameObject* parent = nullptr);

	void set_parent(GameObject* parent);

	GameObject* get_parent();

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

	void AddComponent(Component* component) {
		std::cout << "Add component " << component->name << " to " << this->name << " object.\n";
		_components.push_back(*component);
	}

	std::string get_name() const;

	void set_name(std::string& newName);

	bool isActive() const;

	void setActive(bool active);

	static GameObject swallow_copy(const GameObject& base) {
		GameObject newObj(Transform(*base.transform), base._name + " (Copy)", base._parent);
		/*for (auto component : base._components )
		{
			if (dynamic_cast<Transform*>(component))
				continue;
			auto copy = component;
			newObj.AddComponent(copy);
		}*/
		std::vector<Component> components = base._components;
		newObj._components = components;
		return newObj;
	}

	__declspec(property(get = get_parent	, put = set_parent))	GameObject* parent;
	__declspec(property(get = get_name		, put = set_name))		std::string name;
	__declspec(property(get = getTransform	, put = setTransform))	Transform*	transform;
	__declspec(property(get = getTag		, put = setTag))		std::string tag;
	std::vector<Component>		_components;

private:
	bool						_active;
	bool						_hasChanged;
	std::string					_name;
	std::string					_tag;
	GameObject*					_parent;
	std::vector<GameObject*>	_children;
};

#endif
