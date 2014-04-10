#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

varying mediump vec4 v_Color;
varying mediump vec3 v_Normal;
varying mediump float z;

void main(void)
{
  gl_FragColor = vec4(0,0,0,1);
  float dprod = dot(v_Normal, vec3(0,0,1));
  gl_FragColor.rgb = v_Color.rgb*(0.7 + 1.55*dprod - z*0.015);		  
}
