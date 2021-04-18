//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;
uniform sampler2D diffuseTexture3;
uniform sampler2D diffuseTexture4;
uniform sampler2D splatmapTexture;

uniform vec3 diffuseColor;
uniform vec3 pointLightColor;
uniform vec3 pointLightPosition;
uniform vec3 ambientColor;
uniform vec3 cameraPosition;

uniform float tileMul;

uniform float ambientIntensity = 1.0f;
uniform float specularIntensity = 1.0f;

in vec2 texCoord;

in vec3 Normal;
in vec3 worldPos;

out vec4 fragment_color;

void main( void ) {

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

		vec4 splatInfo = texture(splatmapTexture, texCoord);

		float bgTexAmount = 1 - (splatInfo.r + splatInfo.g + splatInfo.b);
		vec4 bgTexColor = texture(diffuseTexture1, texCoord * tileMul) *splatInfo.r;
		vec4 rTexColor = texture(diffuseTexture2, texCoord * tileMul) * splatInfo.g;
		vec4 gTexColor = texture(diffuseTexture3, texCoord * tileMul) * splatInfo.b;
		vec4 bTexColor = texture(diffuseTexture4, texCoord * tileMul) * splatInfo.a;

		vec4 totalColor = bgTexColor + rTexColor + gTexColor + bTexColor;

		if(pointLightColor != vec3(0,0,0)) fragment_color = totalColor + vec4(result, 1);
		else fragment_color = totalColor;

}
