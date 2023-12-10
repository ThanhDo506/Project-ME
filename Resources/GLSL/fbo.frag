#version 330 core

out vec4 FragColor;

in vec2 UV;

uniform sampler2D screenTexture;

void main()
{    
    vec3 col = texture(screenTexture, UV).rgb;
    FragColor = vec4(col, 1.0);
}