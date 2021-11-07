#version 400 core

## BEGIN_VERTEX
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 col;

void main()
{
   col = aCol;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
## END_VERTEX

## BEGIN_FRAG
in vec3 col;
out vec4 FragColor;

void main()
{
   FragColor = vec4(col, 1.0f);
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
## END_fRAG
