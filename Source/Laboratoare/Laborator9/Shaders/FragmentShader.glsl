#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
uniform bool mix_textures;

in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function

	vec4 clr1 = texture2D(texture_1, texcoord);
	vec4 clr2 = texture2D(texture_2, texcoord);

	if (mix_textures == true) {
		out_color = mix(clr1, clr2, 0.5);
	} else {
		out_color = clr1;
	}
	
	if (out_color.a < 0.5) {
		discard;
	}

	// out_color = vec4(1);
}