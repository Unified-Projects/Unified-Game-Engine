#version 460

in vec3 vs_position;
in vec4 vs_color;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform sampler2D Texture;
uniform vec2[4] UVMap;

void main(){
    // fs_color = texture(Texture, vs_texcoord);
	// fs_color = vec4(0.f, 0.f, 0.f, 1.f);
    fs_color = vs_color;
	
    if(fs_color.a==0.0) discard;
}