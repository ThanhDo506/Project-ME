#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"


class DirectionalLight : public Light {

private:
	Transform* transform;
};

#endif
