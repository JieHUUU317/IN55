#version 140

uniform sampler2D tex;

in vec2 fTexture;
in vec3 fColor;


void main()
{
  gl_FragColor = texture2D( tex, fTexture);
}