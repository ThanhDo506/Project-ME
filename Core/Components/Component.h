#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "../common.h"

class GameObject;

class Component {

public:
	Component(GameObject* gameObject, std::string name, bool isActive = true) : _gameObject(gameObject), _name(name), _active(isActive) {
		APP_CRITICAL("Create Component attach to null GameObject!");
	}

	virtual ~Component();

	virtual void Awake();

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	virtual void OnDestroy();

	virtual void OnEnable();

	virtual void OnDisable();

	std::string getName() const;

	void setName(std::string name);

	void setActive(bool val);

	bool isActive() const;

	GameObject* getGameObject();

	__declspec(property(get = getGameObject)) GameObject* gameObject;
	__declspec(property(get = getName, put = setName)) std::string name;


	Component(const Component& obj, GameObject* gameObject);
	virtual void operator=(const Component& obj);
protected:
	std::string _name;
	bool		_active;
	GameObject* _gameObject;
};

#endif
