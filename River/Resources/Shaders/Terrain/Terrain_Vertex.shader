#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 mvp;
uniform sampler2D texture_diffuse;

void main()
{
	gl_Position = mvp * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}