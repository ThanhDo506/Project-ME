#version 460 core

struct Camera {
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

vec3 get_camera_position(in Camera camera);

vec3 get_camera_position(in Camera camera) {
	return inverse(camera.viewMatrix)[3].xyz;
}