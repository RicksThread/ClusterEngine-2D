#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 projection;
uniform vec4 color;

void main()
{
    gl_Position = projection * transform * rotation * vec4(aPos, 1.0);
    texCoord = uv;
    ourColor = color;
}