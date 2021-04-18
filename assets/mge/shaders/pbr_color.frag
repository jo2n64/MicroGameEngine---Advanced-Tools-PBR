//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

const float PI = 3.14159265359;

//mesh inputs
in vec3 Normal;
in vec3 worldPos;

uniform vec3 cameraPosition;

uniform vec3 pointLightColors[2];
uniform vec3 pointLightPositions[2];

uniform vec3 albedoColor;
uniform float metallic;
uniform float roughness;
uniform float ao;

out vec4 fragment_color;

vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(max(1.0 - cosTheta, 0.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness){
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness){
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness){
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

void main( void ){
    vec3 N = normalize(Normal);
    vec3 V = normalize(cameraPosition - worldPos);
    vec3 Lo = vec3(0.0);
        
    for(int i = 0; i < 2; i++){
        vec3 L = normalize(pointLightPositions[i] - worldPos);
        vec3 H = normalize(V + L);

        float distance = length(pointLightPositions[i] - worldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = pointLightColors[i] * attenuation;

        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedoColor, metallic);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular = numerator / denominator;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedoColor / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedoColor * ao;
    vec3 color = ambient + Lo;
   
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2));

    fragment_color = vec4(color, 1);
    	
}
