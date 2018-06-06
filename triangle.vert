#version 330 core

layout (location = 0) in vec3 position;

out vec3 vertColor;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0);
    vertColor = position;
}
