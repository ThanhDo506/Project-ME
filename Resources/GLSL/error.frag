#version 330 core

out vec4 FragColor;

in VS_OUT {
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texcoord;
	vec3 tangent;
	mat3 tbn;
	vec3 cameraPosition;
	vec3 cameraDirection;
	vec3 worldPosition;
} fs_in;

void main() {
    FragColor = vec4(normalize(fs_in.worldPosition), 1.0);
}
