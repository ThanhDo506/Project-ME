#ifndef SPHERE_H
#define SPHERE_H

#include "../../Components/Component.h"
#include "../../Components/GameObject.h"
#include "../Object/Renderer.h"

class GameObject;

class Sphere : public GameObject
{
public:
	Sphere(Transform transform, float radius = 1.0, int sector = 3, int stack = 2, bool smooth = false);


private:
	float _radius = 1.0;
	int _sectors = 3;
	int _stack = 2;
};

#endif