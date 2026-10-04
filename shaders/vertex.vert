#version 430 core

layout (location = 0) in vec3 v3_inPosition;
layout (location = 1) in vec3 v3_inColor;

layout (location = 0) out vec3 v3_outColor;

void main()
{
    gl_Position = vec4(v3_inPosition, 1.0);
    v3_outColor = v3_inColor;
}
