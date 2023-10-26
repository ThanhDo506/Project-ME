#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "../common.h"

class GameObject;

class Component {

public:
	Component(const Component& base);

	Component(const Component& base, GameObject* owner);

	Component(GameObject* owner, std::string name, bool isActive = true);

	virtual ~Component() = default;

	virtual void Awake();

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	virtual void OnDestroy();

	virtual void OnEnable();

	virtual void OnDisable();

	std::string get_name() const;

	void set_name(std::string name);

	void setActive(bool val);

	bool isActive() const;

	GameObject* get_gameObject();

	virtual Component* Clone(GameObject* gameObject) const = 0;

	__declspec(property(get = get_gameObject, put = set_gameObject))	GameObject* gameObject;
	__declspec(property(get = get_name		, put = set_name))			std::string name;

protected:
	std::string _name;
	bool		_active;
	GameObject* _gameObject;
	
	void set_gameObject(GameObject* gameObject);

	friend class GameObject;
};

#endif
