#shader vertex
#version 330 core

layout(location = 0) in vec3 positions;
layout(location = 1) in vec2 texCoords;

uniform mat4 MVP;

out vec2 UV;

void main() {
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(positions, 1);
	UV = texCoords;
}


#shader fragment
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV).rgb;
};


