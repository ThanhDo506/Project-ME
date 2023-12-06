#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 UV;

uniform mat4 _TransformMatrix;
uniform mat4 _ViewMatrix;
uniform mat4 _ProjectionMatrix;

void main()
{
    UV = aTexCoords;    
    gl_Position = _ProjectionMatrix * _ViewMatrix * _TransformMatrix * vec4(aPosition, 1.0);
}