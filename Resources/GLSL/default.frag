#version 460 core

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

in VS_OUT {
    vec3 CameraPosition;
    vec3 FragmentPosition;
    vec3 Normal;
    vec4 Color;
    vec2 TexCoord;
    vec3 Tangent;
    mat3 TBN;
    vec3 TangentViewPosition;
    vec3 TangentFragPosition;
} fs_in;

uniform Material _Material;

uniform DirectionalLight _DirectionalLights[MAX_DIRECTIONAL_LIGHT];
uniform int _DirectionalLightCount;

uniform PointLight _PointLights[MAX_POINT_LIGHT];
uniform int _PointLightCount;

uniform SpotLight _SpotLights[MAX_SPOT_LIGHT];
uniform int _SpotLightCount;

void main() {
    gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}