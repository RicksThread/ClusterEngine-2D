#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;

out vec4 ourColor;
out vec2 texCoord;

uniform mat4 transform;
uniform mat4 rotation;
uniform mat4 projection;
uniform vec4 color;
uniform mat4 scale;

void main()
{
    gl_Position = projection * transform*(vec4(aPos, 1.0) * scale * rotation);
    texCoord = uv;
    ourColor = color;
}