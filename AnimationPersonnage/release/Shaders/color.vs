#version 140

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 N;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec2 fTexture;
out vec3 sp;
out vec3 unit_normal;

void main()
{
  vec4 pos  = vec4( position, 1.0f );
  gl_Position = MVP*pos;
  fTexture = texcoord;
  sp = vec3( MV *pos);
  unit_normal = normalize( N*normal);
}
