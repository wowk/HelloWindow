#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 coord;

out vec3 posColor;
out vec2 texCoord;
uniform vec3 move;

void main()
{
//    vec3 new_pos = position * 2;
//    gl_Position = vec4(new_pos, 1.0);

//    if( position.y > 0 ){
//        vertColor = vec3(1.0f, 0.0f, 0.0f);
//    }else if( position.x < 0 ){
//        vertColor = vec3(0.0f, 1.0f, 0.0f);
//    }else{
//        vertColor = vec3(0.0f, 0.0f, 1.0f);
//    }

    texCoord = vec2(coord.x, 1-coord.y) + vec2(move.x, -move.y);
    posColor = pos + move;
    gl_Position = vec4(pos + move, 1.0f);
}
