#ifndef CAMERA_REGISTRY_H
#define CAMERA_REGISTRY_H

#include <vector>
#include "../Camera/Camera.h"

class CameraRegistry
{

private:
	std::vector<Camera*> _registry;
};

#endif // !CAMERA_REGISTRY_H
