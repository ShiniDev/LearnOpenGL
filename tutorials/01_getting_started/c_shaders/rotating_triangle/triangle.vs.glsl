#version 330 core
layout(location = 0) in vec3 aPos;

out vec4 ourColor;

uniform float angle;

vec2 my_rotate(vec2 p, float angle) {
    float o_x = p.x;
    float o_y = p.y;
    p.x = o_x * cos(angle) - o_y * sin(angle);
    p.y = o_x * sin(angle) + o_y * cos(angle);
    return p;
}

void main()
{
    gl_Position = vec4(my_rotate(aPos.xy, angle), aPos.z, 1.0);
    // gl_Position = vec4(aPos, 1.0);
    ourColor = gl_Position;
}