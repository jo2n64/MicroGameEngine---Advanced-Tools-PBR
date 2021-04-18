//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 Normal;
out vec3 FragPos;

void main( void ){
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
	texCoord = uv;
	Normal = normal;
	FragPos = vec3(modelMatrix * vec4(vertex, 1)); 
}
