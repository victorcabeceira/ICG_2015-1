#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec4 vColor;


uniform mat4 ModelView;
uniform mat4 Projection;

out vec4 color; 
void main()
{
    color = vColor;
    gl_Position = Projection*ModelView*vec4(vPosition, 1.0); 
}
