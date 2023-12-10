#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 _ProjectionMatrix;
uniform mat4 _ViewMatrix;
uniform mat4 _TransformMatrix;

void main()
{
    TexCoords = aPos;
    vec4 pos = _ProjectionMatrix * _ViewMatrix * _TransformMatrix * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
} 