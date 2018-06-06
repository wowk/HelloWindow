#version 330 core

out vec4 color;
uniform vec3 custColor;

void main()
{
    color = vec4(custColor, 1.0f);
}
