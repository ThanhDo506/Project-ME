#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light.h"

class Light;

class PointLight : public Light {

private:
	float range;
};

#endif
