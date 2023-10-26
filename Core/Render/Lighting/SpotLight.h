#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Light.h"

class Light;

class SpotLight : public Light {

private:
	float innerAngle;
	float outterAngle;
};

#endif
