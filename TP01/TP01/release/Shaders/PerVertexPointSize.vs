#version 140


uniform mat4 MVP;

in vec3 position;
in vec3 color;

out vec3 fColor;


void main()
{
  gl_Position = MVP * vec4( position, 1.0f );
  gl_PointSize = gl_Position.z;
  fColor = color;
}