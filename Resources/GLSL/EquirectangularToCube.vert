#version 330 core
layout (location = 0) in vec3 aPosition;

out vec3 WorldPosition;

uniform mat4 _ProjectionMatrix;
uniform mat4 _ViewMatrix;

void main()
{
    WorldPosition = aPosition;
    gl_Position =  _ProjectionMatrix * _ViewMatrix * vec4(WorldPosition, 1.0);
}