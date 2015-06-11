#version 120

uniform sampler2D tex;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;

in vec2 fTexture;
in vec3 sp;
in vec3 unit_normal;

void main()
{
  vec3 ct, cf; 
  float af, at;
  vec4 texture = texture2D( tex, fTexture);
  vec3 V = -normalize( sp );
  vec3 ambient = vec3(0.0);
  vec3 diffuse = vec3(0.0);
  vec3 specular = vec3(0.0);
   float nDotLi; 	// normal . light direction
   float nDotH; 	// normal . light half vector
   float pf; 		// power factor
   float spotDot; 	// cosine of angle between spotlight
   float spotAttenuation; 	// spotlight attenuation factor
   float attenuation; 		// computed attenuation factor
   float d; 		// distance from surface to light source
   vec3 L; 		// direction from surface to light position
   vec3 halfway_vector; 	// direction of maximum highlights
   vec4 sourcePos = gl_LightSource[0].position;
   sourcePos =  MV * sourcePos ;
   L = sourcePos.xyz - sp ;
   d = length( L );
   L = normalize( L );

   attenuation = 1.0 / (gl_LightSource[0].constantAttenuation + gl_LightSource[0].linearAttenuation * d +   gl_LightSource[0].quadraticAttenuation *d * d);
   halfway_vector = normalize(L + V);

   nDotLi = max(0.0, dot(unit_normal, L));
   nDotH = max(0.0, dot(unit_normal, halfway_vector));
   if (nDotLi == 0.0)
      pf = 0.0;
   else
      pf = nDotH;

   ambient += gl_LightSource[0].ambient.rgb;
   diffuse  += gl_LightSource[0].diffuse.rgb * nDotLi * attenuation; 
   specular += gl_LightSource[0].specular.rgb * pf * attenuation;
   af =  gl_LightSource[0].diffuse.a;
   ct = texture.rgb;
   at = texture.a;
   gl_FragColor=  vec4(ct * (ambient + diffuse+specular), at * af) ;
}