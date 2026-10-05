#version 430 core

layout (location = 0) in vec3 v3_inColor;

layout (location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(v3_inColor, 1.0);
}
