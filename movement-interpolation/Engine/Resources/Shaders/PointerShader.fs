#version 330 core
out vec4 FragColor;

uniform float opacity;

in vec3 color;

void main()
{
    FragColor = vec4(color, opacity);
}
