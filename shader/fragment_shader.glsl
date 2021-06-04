#version 410 core

in vec3	color_shader;

out vec4 outColor;

void	main()
{
	outColor = vec4(color_shader, 1.0);
}
