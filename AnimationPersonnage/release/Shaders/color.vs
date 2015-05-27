#version 140

uniform mat4 MVP;

in vec3 position;
in vec2 texcoord;

out vec2 fTexture;

void main()
{
  gl_Position = MVP * vec4( position, 1.0f );
  fTexture = texcoord;
}
