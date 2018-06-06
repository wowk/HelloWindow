#version 330 core

in vec3 posColor;
in vec2 texCoord;
out vec4 color;
uniform vec3 custColor;
uniform sampler2D textureSampler;


void main()
{
    //color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    color = texture2D(textureSampler, texCoord);
}
