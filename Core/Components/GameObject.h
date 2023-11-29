#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include "Component.h"
#include "../common.h"
#include "../Scene/Scene.h"

class Component;
class Transform;

class GameObject {
	friend class Transform;
	friend class Component;
	friend class Scene;
public:
	std::unordered_map<std::type_index, Component*> _components;
	std::vector<GameObject*>						_children;

private:
	bool											_active;
	bool											_hasChanged = true;
	std::string										_name;
	std::string										_tag;
	Scene* _scene;
	/// <summary>
	/// Please use parent/set_parent to modify
	/// It will change children attribute of _parent
	/// </summary>
	GameObject* _parent;

public:
	GameObject(const GameObject& baseGameObject);

	GameObject(const GameObject& baseGameObject,
		Transform transform,
		std::string name = "Game Object",
		GameObject* parent = nullptr);

	GameObject(Transform transform,
		std::string name = "Game Object",
		GameObject* parent = nullptr,
		bool isActive = true);

	~GameObject();

	void set_parent(GameObject* parent);
	GameObject* get_parent();

	GameObject* FindInChild(std::string name);

	bool IsChildOf(const GameObject* gameObject) const;
	/// <summary>
	/// Delete completely the child GameObject. TODO: should make return std::unique_ptr removed GameObject.
	/// </summary>
	/// <param name="instance"></param>
	void RemoveChild(GameObject* instance);

	Scene* get_scene();

	#pragma region Behavior
	/// <summary>
	///	This called when GameObject::set_active(true)
	/// </summary>
	virtual void OnEnable();
	/// <summary>
	///	This called when GameObject::set_active(false)
	/// </summary>
	virtual void OnDisable();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy(GameObject* instance, float time = 0.0f);
	// TODO: i haven't done this :D
	virtual void Destroy(Component* component, float time = 0.0f);
	#pragma endregion

	std::string get_name() const;
	void set_name(const std::string newName);

	std::string get_tag() const;
	void set_tag(std::string tag);

	/// <summary>
	/// When set active, it 'll send its and its Component method OnEnable/OnDisable to EventHandler
	/// </summary>
	/// <param name="active">state of GameObject</param>
	void set_active(bool active);
	bool is_active() const;

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args) {
		T* component = new T(std::forward<Args>(args)...);
		this->_components.insert(std::make_pair<std::type_index, Component*>(typeid(T), component));
		component->_gameObject = this;
		return component;
	}

	template <typename T>
	bool HasComponent() {
		return (this->_components.find(typeid(T)) != this->_components.end());
	}

	template<typename T>
	T* GetComponent() {
		auto it = this->_components.find(typeid(T));
		if (it != this->_components.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	void RemoveComponent() {
		if (HasComponent<T>()) {
			T* component = GetComponent<T>();
			this->_components.erase(typeid(T));
			if (!HasComponent<T>()) {
				APP_INFO("Erased component %s from %s now safe to delete!", typeid(component).name(), this->_name.c_str());
				return;
			}
			delete component;
		}
	}

	__declspec(property(get = get_parent, 
						put = set_parent))		GameObject* parent;
	__declspec(property(get = get_name,
						put = set_name))		std::string name;
	__declspec(property(get = get_tag,
						put = set_tag))			std::string tag;
	__declspec(property(get = get_scene))		Scene*		scene;
};

#endif
