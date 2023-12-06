#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoord;
layout (location = 4) in vec3 aTangent;

struct Camera {
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

vec3 get_camera_position(in Camera camera);
mat3 get_TBN(in vec3 tangent,in vec3 normal);

uniform Camera	_Camera;
uniform mat4	_TransformMatrix;

out VS_OUT {
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texcoord;
	vec3 tangent;
	mat3 tbn;
	vec3 cameraPosition;
	vec3 cameraDirection;
	vec3 worldPosition;
} vs_out;


void main() {
	vs_out.position = aPosition;
	vs_out.normal = aNormal;
	vs_out.color = aColor;
	vs_out.texcoord = aTexCoord;
	vs_out.tangent = aTangent;
	vs_out.tbn = get_TBN(aTangent,aNormal);
	vs_out.cameraPosition = get_camera_position(_Camera);
	vs_out.cameraDirection = normalize(vec3(_Camera.viewMatrix[2]));
	vs_out.worldPosition = vec3(_TransformMatrix * vec4(aPosition, 1.0));
	gl_Position = _Camera.projectionMatrix * _Camera.viewMatrix * _TransformMatrix * vec4(aPosition, 1.0);
}


vec3 get_camera_position(in Camera camera) {
	return inverse(camera.viewMatrix)[3].xyz;
}


mat3 get_TBN(in vec3 tangent, in vec3 normal) {
    vec3 T = normalize(vec3(_TransformMatrix * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(_TransformMatrix * vec4(normal, 0.0)));
    // re-orthogonalize T with respect to N
    T = normalize(T - dot(T, N) * N);
    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 B = cross(N, T);
    return mat3(T, B, N);
}