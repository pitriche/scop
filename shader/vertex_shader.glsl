#version 410 core

uniform float screen_ratio;

in vec3 position;
in vec3 color;

out vec3 color_shader;

void	main()
{
	color_shader = color;
	gl_Position = vec4(position.x * 0.7 / screen_ratio, position.y * 0.7,
		0.0, 1.0);
}
