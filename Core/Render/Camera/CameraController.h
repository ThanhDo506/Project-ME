#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "../../common.h"
#include "../../Components/Component.h"
#include "Camera.h"
#include "../../Events/Input.h"
#include "../../Time/Time.h"

class CameraController : public Component
{
public:
    CameraController(float speed = 3.5f,
        float sensitivityX = 200.0f,
        float sensitivityY = 200.0f);
    void Update() override;
    void set_camera(Camera* camera);

    CameraController* Clone() const override;
private:
    bool    _isForcus;
    float   _speed;

    float _sensitivityX;
    float _sensitivityY;
    float rotationX;
    float rotationY;

    Camera* _camera = nullptr;

    void camera_movement();
    void camera_rotation();
};

#endif