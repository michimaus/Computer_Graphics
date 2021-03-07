#version 330
 
uniform sampler2D texture_1;

in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position[75];
uniform vec3 spot_light_position;
uniform vec3 eye_position;

uniform int number_ligh_sources;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int spotlight;

in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 clr1 = texture2D(texture_1, texcoord);
	out_color = clr1;

	float light;
	float ambient_light = 0.85;
	light = ambient_light;

	for (int i = 0; i < number_ligh_sources; i++) {
		vec3 N = normalize(world_normal);
		vec3 L = normalize(light_position[i] - world_position);
		vec3 V = normalize(eye_position - world_position);
		vec3 H = normalize(L + V);

		float diffuse_light = material_kd * max(dot(normalize(N), L), 0);
		float specular_light = 0;

		if (diffuse_light > 0) {
			specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
		}

		float d = distance(light_position[i], world_position);
		float attenuation_factor = 10000.f / max(d * (d * 1.0), 10000.f);
		light += attenuation_factor * (diffuse_light + specular_light);
	}

	vec3 N = normalize(world_normal);
	vec3 L = normalize(spot_light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	float diffuse_light = material_kd * max(dot(normalize(N), L), 0);
	float specular_light = 0;

	if (diffuse_light > 0) {
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	float cut_off = radians(60);
	float spot_light = dot(-L, light_direction);
	
	if (spot_light > cos(cut_off)) {	
		float spot_light_limit = cos(cut_off);
		float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
		float light_att_factor	= linear_att * linear_att * linear_att;
		light +=  light_att_factor * (diffuse_light + specular_light);
	} 

	out_color = vec4(vec3(clr1 * light), 1);
}