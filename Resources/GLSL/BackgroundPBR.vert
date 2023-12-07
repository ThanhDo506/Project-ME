#version 330 core

layout (location = 0) in vec3 aPosition;

uniform mat4 _ProjectionMatrix;
uniform mat4 _ViewMatrix;

out vec3 WorldPosition;

void main()
{
    WorldPosition = aPosition;

	mat4 rotView = mat4(mat3(_ViewMatrix));
	vec4 clipPos = _ProjectionMatrix * rotView * vec4(WorldPosition, 1.0);

	gl_Position = clipPos.xyww;
}