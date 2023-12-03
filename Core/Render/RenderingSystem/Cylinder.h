#ifndef CYLINDER_H
#define CYLINDER_H

#include "../../Components/Component.h"
#include "../../Components/GameObject.h"
#include "../Object/Renderer.h"

class GameObject;

class Cylinder : public GameObject
{
public:
	Cylinder(Transform transform);

};

#endif // !CYLINDER_H
