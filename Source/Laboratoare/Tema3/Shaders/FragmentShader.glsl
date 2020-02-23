#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
in vec2 texcoord;
in float Light;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 color1= texture2D(texture_1, texcoord);
	vec4 color2= texture2D(texture_2, texcoord);
	vec4 color = mix(color1, color2, 0.5f);
	float alpha = color.a;
	if(alpha < 0.5f)
		discard;
	out_color = vec4(vec3(Light) * color.xyz, 1);
}