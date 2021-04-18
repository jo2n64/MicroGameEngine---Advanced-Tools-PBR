//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
in vec2 texCoord;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 pointLightColor;
uniform vec3 pointLightPosition;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 cameraPosition;

uniform float ambientIntensity = 1.0f;
uniform float specularIntensity = 1.0f;

out vec4 fragment_color;

void main( void ) {
	vec3 ambientTerm = ambientIntensity * ambientColor * diffuseColor;

	vec3 normal = normalize(Normal);
	vec3 lightDir = pointLightPosition - FragPos;
	float lightDist = length(lightDir);
	vec3 lightDirNormalized = normalize(lightDir);
	float diffuse = max(0, dot(lightDirNormalized, normal));
	diffuse /= (1 + lightDist + 0 * lightDist * lightDist);

	vec3 diffuseTerm = diffuse * pointLightColor * diffuseColor;

	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDirNormalized, normal);
	float spec = pow(max(0, dot(viewDir, reflectDir)), 32);
	vec3 specularTerm = specularIntensity * spec * pointLightColor;

	vec3 result = ambientTerm + diffuseTerm + specularTerm;
	if(pointLightColor != vec3(0,0,0))fragment_color = vec4(result, 1) + texture(diffuseTexture,texCoord);
	else{
		fragment_color = texture(diffuseTexture,texCoord);
	}
}
