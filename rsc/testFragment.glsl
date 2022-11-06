#version 460

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform vec3 CameraPosition;
uniform vec3 CameraFront;

void main(){
	//Final
	fs_color = vec4(vs_color, 1.f);

	if(fs_color.a==0.0) discard;
	
	// fs_color = vec4(1.f, 1.f, 1.f, 1.f);
}
