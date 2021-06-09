#version 410 core

uniform sampler2D	texture_sampler;
uniform float		blending;

in vec3		color_geometry;
in vec2		texture_position_geometry;

out vec4	outColor;

void	main()
{
	vec4	tmp_tex;
	vec4	tmp_facet;

	tmp_tex = vec4(texture(texture_sampler, texture_position_geometry));
	tmp_facet = vec4(color_geometry, 1.0);

	outColor = mix(tmp_tex, tmp_facet, blending);
}
