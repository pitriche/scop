#version 410 core

uniform float	screen_ratio;
uniform mat4	model_matrix;
uniform mat4	view_matrix;
uniform mat4	projection_matrix;

in vec3			position;
in float		color_grey;

// out vec3		color_textureshader;
out vec3		color_shader;

void	main()
{
	vec4	tmp_pos;
	vec3	greyshade_color;
	vec3	texture_color;

	/* get greyshade color */
	greyshade_color = vec3(color_grey);

	/* get texture color */
	texture_color = vec3(1.0, 0.0, 0.0);

	/* get final color using mix uniform */
	color_shader = mix(greyshade_color, texture_color, 0.0);


	/* get coordonates */
	tmp_pos = vec4(position, 1.0);
	gl_Position = projection_matrix * view_matrix * model_matrix * tmp_pos;
}
