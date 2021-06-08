#version 410 core

uniform float	screen_ratio;
uniform mat4	model_matrix;
uniform mat4	view_matrix;
uniform mat4	projection_matrix;

in vec3			position;

out vec3		color_shader;

void	main()
{
	vec4	tmp_pos;

	/* set color to white */
	color_shader = vec3(sin(position.x), 0.05, -sin(position.x));

	tmp_pos = vec4(position, 1.0);
	gl_Position = projection_matrix * view_matrix * model_matrix * tmp_pos;
}
