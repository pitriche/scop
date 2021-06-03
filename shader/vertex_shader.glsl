#version 410 core

in vec3 position;

void	main()
{
	gl_Position = vec4(position.x / 0.5, position.y / 0.5, 0.0, 1.0);
}
