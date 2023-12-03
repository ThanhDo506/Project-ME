#version 330 core

const float PI = 3.14159265359;

#ifndef GAMMA
#define GAMMA 2.2
#endif

#ifndef MAX_DIRECTIONAL_LIGHT
#define MAX_DIRECTIONAL_LIGHT 100
#endif

#ifndef MAX_POINT_LIGHT
#define MAX_POINT_LIGHT 100
#endif

#ifndef MAX_SPOT_LIGHT
#define MAX_SPOT_LIGHT 100
#endif

struct Material {
    sampler2D diffuseMap;
    sampler2D roughnessMap;
    vec2 tilling;
    vec2 offset;
};

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3    direction;
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
    float   intensity;
};

struct PointLight {
    vec3        position;
    vec3        ambient;
    vec3        diffuse;
    vec3        specular;
    float       intensity;
    Attenuation attenuation;
};

struct SpotLight {
    vec3    position;
    vec3    direction;
    float   innerAngle;
    float   outerAngle;

    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
    float   intensity;
    Attenuation attenuation;
};

void calculate_TilingAndOffset(inout vec2 UV, vec2 Tiling, vec2 Offset);

in VS_OUT {
	vec3 position;
	vec3 normal;
	vec4 color;
	vec2 texcoord;
	vec3 tangent;
	mat3 tbn;
	vec3 cameraPosition;
	vec3 cameraDirection;
} fs_in;

uniform Material _Material;

uniform DirectionalLight _DirectionalLights[MAX_DIRECTIONAL_LIGHT];
uniform int _DirectionalLightCount;

uniform PointLight _PointLights[MAX_POINT_LIGHT];
uniform int _PointLightCount;

uniform SpotLight _SpotLights[MAX_SPOT_LIGHT];
uniform int _SpotLightCount;

void main() {
//    gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
//    calculate_TilingAndOffset(fs_in.texcoord, _Material.tilling, _Material.offset);
    gl_FragColor = mix(fs_in.color, 
    mix(
        texture(_Material.diffuseMap, fs_in.texcoord * _Material.tilling + _Material.offset), 
        texture(_Material.roughnessMap, fs_in.texcoord * _Material.tilling + _Material.offset), 0.5), 0.9);
}

void calculate_TilingAndOffset(inout vec2 UV, vec2 Tiling, vec2 Offset)
{
    UV = UV * Tiling + Offset;
}