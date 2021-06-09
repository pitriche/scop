#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3		color_vertex[];
in vec2		texture_position_vertex[];

out vec3		color_geometry;
out vec2		texture_position_geometry;

void main()
{
	gl_Position = gl_in[0].gl_Position;
	color_geometry = color_vertex[1];
	texture_position_geometry = texture_position_vertex[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	color_geometry = color_vertex[1];
	texture_position_geometry = texture_position_vertex[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	color_geometry = color_vertex[1];
	texture_position_geometry = texture_position_vertex[2];
	EmitVertex();

	EndPrimitive();
}