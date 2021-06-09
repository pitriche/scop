#version 410 core

uniform mat4	model_matrix;
uniform mat4	view_matrix;
uniform mat4	projection_matrix;

in vec3			position;
in float		color_grey;

out vec3		color_vertex;
out vec2		texture_position_vertex;

void	main()
{
	vec4	tmp_pos;

	/* get greyshade color */
	color_vertex = vec3(color_grey);

	/* get texture position */
	texture_position_vertex = vec2(position.z / 3 + 0.5, position.y / 1.5 + 0.5);


	/* get coordonates */
	tmp_pos = vec4(position, 1.0);
	gl_Position = projection_matrix * view_matrix * model_matrix * tmp_pos;
}
