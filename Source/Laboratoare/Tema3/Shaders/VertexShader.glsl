#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties 
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D heightmap;
uniform int HeightMapWidth;
uniform int HeightMapHeight;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

out vec2 texcoord;
out float Light;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;
	vec3 vertex = v_position;
	vertex.y = texture(heightmap, v_texture_coord).r * 4.0f;

	float height = texture2D(heightmap, v_texture_coord).r * 4.0f;
	vec2 texelSize = vec2(1.0f/HeightMapWidth, 1.0f/HeightMapHeight);
	float heightRight = texture2D(heightmap, vec2(v_texture_coord.x + texelSize.x, v_texture_coord.y)).r * 4.0f;
	float heightUp = texture2D(heightmap, vec2(v_texture_coord.x, v_texture_coord.y  + texelSize.y)).r * 4.0f;
	float Hx, Hz;
	Hx = height - heightRight;
	Hz = height - heightUp;
	vec3 normal = normalize(vec3(Hx * 2.0f, 1, Hz * 2.0f));

	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * normal );
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );

	float ambient_light = 0.25;
	float diffuse_light = material_kd * max(dot(world_normal, L), 0);
	float specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);
	if (diffuse_light > 0)
	{
	}
	float d = distance(L, v_position);
	float Fa = 1 / (0.1 * d * d + 0.02 * d + 1);
	Light = ambient_light + (diffuse_light + specular_light) * Fa;

	gl_Position = Projection * View * Model * vec4(vertex, 1.0);
}
