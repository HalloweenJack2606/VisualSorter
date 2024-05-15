#shader vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 color;

void main()
{
    color = aColor;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}

#shader fragment
#version 410 core
out vec4 FragColor;
in vec4 color;

void main()
{
    FragColor = color;
} 