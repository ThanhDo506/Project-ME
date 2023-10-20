#ifndef Component_H
#define Component_H

#include <string>
#include "GameObject.h"

class GameObject;
class Transform;

class Component {

public:
	Component(GameObject* gameObject, std::string name, bool isActive = true);

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

protected:
	std::string _name;
	bool		_active;
	GameObject* _gameObject;
};

#endif
