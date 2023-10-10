#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

class IComponent {

private:
	std::string _name;
	bool _active;

public:
	virtual ~IComponent() {}

	virtual void Awake();

	virtual void Start();

	virtual void Update();

	virtual void FixedUpdate();

	virtual void OnDestroy();

	virtual void OnEnable();

	virtual void OnDisable();

	std::string getName() const;

	void setName(const char* name);

	void setActive(bool active);

	bool isActive() const;
};

#endif
