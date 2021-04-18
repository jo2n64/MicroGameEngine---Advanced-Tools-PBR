//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1


//mesh inputs
in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

//world space variables to send to frag shader
out vec3 Normal;
out vec3 worldPos;

void main( void ){
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.f);
        //Normal = normal; // not converted to world space since the current structure isn't nested
        Normal = vec3(modelMatrix * vec4(normal, 0.0f)); //but just in case, if we were to have nested structures
        worldPos = vec3(modelMatrix * vec4(vertex, 1.0f));
}
