#version 330 core
out vec4 FragColor;
in vec3 WorldPosition;

uniform samplerCube _EnvironmentMap;

void main()
{		
    vec3 envColor = texture(_EnvironmentMap, WorldPosition).rgb;
    
    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2)); 
    
    FragColor = vec4(envColor, 1.0);
}