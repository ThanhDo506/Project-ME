#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 position;
	vec3 normal;
	vec4 color;
	vec2 uv;
	vec3 tangent;
	mat3 tbn;
	vec3 cameraPosition;
	vec3 cameraDirection;
	vec3 worldPosition;
} fs_in;

const float PI = 3.14159265359;

#ifndef GAMMA
#define GAMMA 2.2
#endif

#ifndef MAX_DIRECTIONAL_LIGHT
#define MAX_DIRECTIONAL_LIGHT 10
#endif

#ifndef MAX_POINT_LIGHT
#define MAX_POINT_LIGHT 10
#endif

#ifndef MAX_SPOT_LIGHT
#define MAX_SPOT_LIGHT 10
#endif

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
};

struct PointLight {
    vec3        position;
    vec3        color;
    float       radius;
	float       intensity;

    Attenuation attenuation;
    vec3        ambient;
    vec3        specular;
    vec3        diffuse;
};

struct SpotLight {
    vec3        position;
    vec3        color;
    vec3        direction;
    float       innerAngle;
    float       outerAngle;
	float       intensity;
    Attenuation attenuation;
};

struct Material {
    sampler2D   diffuseMap;
    sampler2D   roughnessMap;
    sampler2D   metallicMap;
    sampler2D   aoMap;
    sampler2D   normalMap;
    sampler2D   emissionMap;
    sampler2D   parallaxMap;

    vec2        tilling;
    vec2        offset;

    float       metallic;
	float       smoothness;
	float       aoStrength;
	float       alphaClippingThreshold;
	bool		useAlphaClipping;
    bool        useEmission;
    bool        useMetallic;

    vec3        ambient;
    vec3        specular;
    vec3        diffuse;
};

uniform Material _Material;

uniform DirectionalLight _DirectionalLights[MAX_DIRECTIONAL_LIGHT];
uniform int _DirectionalLightCount;

uniform PointLight _PointLights[MAX_POINT_LIGHT];
uniform int _PointLightCount;

uniform SpotLight _SpotLights[MAX_SPOT_LIGHT];
uniform int _SpotLightCount;

uniform bool _UseBlinnPhong;

/************************** LIGHTING ************************/
float calculateAttenuation(Attenuation attenuation, float distance);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection); 
vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection);
/***********************************************************/

/*************************** PBR ****************************/
vec3 getNormalFromMap();
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);

/************************************************************/

void main() {
    vec3 albedo = pow(texture(_Material.diffuseMap, fs_in.uv).rgb, vec3(GAMMA));
    float metallic = texture(_Material.metallicMap, fs_in.uv).r;
    float roughness = texture(_Material.roughnessMap, fs_in.uv).r;
    float ao = texture(_Material.aoMap, fs_in.uv).r;
    vec3 N = getNormalFromMap();

    vec3 V = normalize(fs_in.cameraPosition - fs_in.worldPosition);
    vec3 R = reflect(-V, N); 

    vec3 F0 = vec3(0.04);   
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.004);

    for (int i = 0; i < _PointLightCount; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(_PointLights[i].position - fs_in.worldPosition);
        vec3 H = normalize(V + L);
        float distance = length(_PointLights[i].position - fs_in.worldPosition);
        float attenuation = 1.0 / max((distance * distance), 10e-5);
        vec3 radiance = _PointLights[i].color * attenuation * _PointLights[i].intensity;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);    
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);        
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
         // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	                
            
        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    
    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0 / GAMMA)); 

    FragColor = vec4(color, 1.0);
}

/*************************** LIGHTING ******************************/
float calculateAttenuation(Attenuation attenuation, float distance) {
    // Avoid dividing by zero.
    return 1.0 / max(attenuation.constant + attenuation.linear * distance
    + attenuation.quadratic * distance * distance, 1e-5);
}

/*******************************************************************/

/**************************** PBR **********************************/

vec3 getNormalFromMap() {
    vec3 tangentNormal = texture(_Material.normalMap, fs_in.uv).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(fs_in.worldPosition);
    vec3 Q2  = dFdy(fs_in.worldPosition);
    vec2 st1 = dFdx(fs_in.uv);
    vec2 st2 = dFdy(fs_in.uv);

    vec3 N   = normalize(fs_in.normal);
    vec3 T  = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
} 
/*******************************************************************/



//vec3 calculateNormalPointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection)
//{
//    vec3 lightDir = normalize(light.position - fragmentPosition);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    float spec = 0.0;
//    if(_UseBlinnPhong) {
//        vec3 halfwayDir = normalize(lightDir + cameraDirection);
//        spec = pow(max(dot(normal, halfwayDir), 0.0), _Material.shininess);
//    } else {
//        vec3 reflectDir  = reflect(-lightDir, normal);
//        spec = pow(max(dot(cameraDirection, reflectDir), 0.0), _Material.shininess);
//    }
//    // attenuation
//    float distance    = length(light.position - fragmentPosition);
//    float attenuation = calculateAttenuation(light.attenuation, distance);
//    // combine results
//    vec3 ambient  = light.ambient  * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 diffuse  = light.diffuse  * diff * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 specular = light.specular * spec * vec3(texture(_Material.specularMaps[0], fs_in.TexCoord));
//    ambient  *= attenuation;
//    diffuse  *= attenuation;
//    specular *= attenuation;
//    return (ambient + diffuse + specular);
//}
//
//vec3 calculateNormalDirectionalLight(DirectionalLight light, vec3 normal, vec3 cameraDirection)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    float spec = 0;
//    if(_UseBlinnPhong) {
//        vec3 halfwayDir = normalize(lightDir + cameraDirection);
//        spec = pow(max(dot(normal, halfwayDir), 0.0), _Material.shininess);
//    } else {
//        vec3 reflectDir  = reflect(-lightDir, normal);
//        spec = pow(max(dot(cameraDirection, reflectDir), 0.0), _Material.shininess);
//    }
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 specular = light.specular * spec * vec3(texture(_Material.specularMaps[0], fs_in.TexCoord));
//    return (ambient + diffuse + specular);
//}
//
//vec3 calculateNormalSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 cameraDirection) {
//    vec3 lightDir = normalize(light.position - fragmentPosition);
//    // diffuse shading
//    float diff = max(dot(normal, lightDir), 0.0);
//    // specular shading
//    float spec = 0;
//    if(_UseBlinnPhong) {
//        vec3 halfwayDir = normalize(lightDir + cameraDirection);
//        spec = pow(max(dot(normal, halfwayDir), 0.0), _Material.shininess);
//    } else {
//        vec3 reflectDir  = reflect(-lightDir, normal);
//        spec = pow(max(dot(cameraDirection, reflectDir), 0.0), _Material.shininess);
//    }
//    // attenuation
//    float distance = length(light.position - fragmentPosition);
//    float attenuation = calculateAttenuation(light.attenuation, distance);
//    // spotlight intensity
//    float theta = dot(lightDir, normalize(-light.direction));
//    float epsilon = light.innerAngle - light.outerAngle;
//    float intensity = clamp((theta - light.outerAngle) / epsilon, 0.0, 1.0);
//    // combine results
//    vec3 ambient = light.ambient * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 diffuse = light.diffuse * diff * vec3(texture(_Material.diffuseMaps[0], fs_in.TexCoord));
//    vec3 specular = light.specular * spec * vec3(texture(_Material.specularMaps[0], fs_in.TexCoord));
//    ambient *= attenuation * intensity;
//    diffuse *= attenuation * intensity;
//    specular *= attenuation * intensity;
//    return (ambient + diffuse + specular);
//}