//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 Normal;
in vec3 worldPos;

uniform vec3 diffuseColor;
uniform vec3 pointLightColor;
uniform vec3 pointLightPosition;
uniform vec3 ambientColor;
uniform vec3 cameraPosition;

uniform float ambientIntensity = 1.0f;
uniform float specularIntensity = 1.0f;

out vec4 sColor;
out vec4 fragment_color;

void main( void ) {
	
	if(pointLightColor == vec3(0,0,0)){
		fragment_color = vec4(diffuseColor, 1);
	}
	else{
		//ambient term
		vec3 ambientTerm = ambientColor * diffuseColor;

		//diffuse term
		vec3 normal = normalize(Normal);
		vec3 lightDir = pointLightPosition - worldPos;
		float lightDist = length(lightDir);
		vec3 lightDirNormalized = normalize(lightDir);
		float diffuseIntensity = max(0, dot(lightDirNormalized, normal));
		float att = 1/ (1 + lightDist);
		vec3 diffuseTerm = att * diffuseIntensity * pointLightColor * diffuseColor;

		//specular term
		vec3 viewDir = normalize(cameraPosition - worldPos);
		vec3 reflectDir = reflect(-lightDirNormalized, normal);
		float spec = pow(max(0, dot(viewDir, reflectDir)), specularIntensity);
		vec3 specularTerm = att * spec * pointLightColor;

		vec3 result = ambientTerm + diffuseTerm + specularTerm;
		fragment_color = vec4 (result,1);
	}
}
