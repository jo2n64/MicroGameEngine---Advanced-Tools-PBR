//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1


uniform float heightModifier;
uniform sampler2D heightmapTexture;

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
	float heightModifier = texture(heightmapTexture, uv).b * heightModifier;
	vec3 deformedVertex = vec3(vertex.x, heightModifier, vertex.z);
	vec3 neighborVertex = vec3(vertex.x + 1/8192.0f, deformedVertex.y, vertex.z + 1/8192.0f);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(deformedVertex, 1.f);
	texCoord = uv;
	Normal = cross(deformedVertex, neighborVertex); //(should be converting to) world normal
	FragPos = vec3(modelMatrix * vec4(vertex, 1)); //world pos
}
