#version 330 core
layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_InstancePosition;

uniform mat4 u_ViewProjection;

void main()
{
    vec3 worldPos = in_Position + in_InstancePosition;
    gl_Position = u_ViewProjection * vec4(worldPos, 1.0);  
}