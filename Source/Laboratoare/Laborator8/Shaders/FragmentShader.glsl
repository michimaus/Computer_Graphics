#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

uniform int is_spot_light;
uniform float cut_off_angle;

layout(location = 0) out vec4 out_color;

void main() {
	// TODO: define ambient light component
	float ambient_light = 0.25;

	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));


	// TODO: compute diffuse light component
	float diffuse_light = 0;

	if (dot(normalize(N), L) > 0) {
		diffuse_light = material_kd * dot(normalize(N), L);
	}

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0 && dot(N, H) > 0) {
		specular_light = material_ks * pow(dot(N, H), material_shininess);
	}


	float light = 0;

	// TODO: compute light
	if (is_spot_light == 1) {

		float spot_light = dot(-L, light_direction);

		float cut_off_rad = radians(cut_off_angle);
		float spot_light_limit = cos(cut_off_rad);
		
		if (spot_light > spot_light_limit) {

			float linear_att = (spot_light - spot_light_limit) / (1.f - spot_light_limit);

			// float light_att_factor = linear_att * linear_att;
			light = ambient_light + linear_att * linear_att * (diffuse_light + specular_light);

		} else {
			light = ambient_light; 
		}

	} else {
		float myDist = distance(light_position, world_position);
		// float attenuation_factor = 1.f / max(myDist * myDist, 1.f);
		light = ambient_light + 1.f / max(myDist * myDist, 1.f) * (diffuse_light + specular_light);
	}

	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1);
}