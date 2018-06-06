#version 330 core

layout (location = 0) in vec3 position;

out vec3 vertColor;

void main()
{
    vec3 new_pos = position * 2;
    gl_Position = vec4(new_pos, 1.0);

    if( position.y > 0 ){
        vertColor = vec3(1.0f, 0.0f, 0.0f);
    }else if( position.x < 0 ){
        vertColor = vec3(0.0f, 1.0f, 0.0f);
    }else{
        vertColor = vec3(0.0f, 0.0f, 1.0f);
    }
}
