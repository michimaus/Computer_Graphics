#version 330

// TODO: get values from fragment shader
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
uniform bool mix_textures;

in vec2 texcoord;

void main() {

	out_color = vec4(frag_normal, 1);
	out_normal = vec4(frag_normal, 1);
	out_texture = vec3(frag_texture, 1);

	// vec4 clr1 = texture2D(texture_1, texcoord);
	// out_color = clr1;

	// if (out_color.a < 0.5) {
		// discard;
	// }	
}