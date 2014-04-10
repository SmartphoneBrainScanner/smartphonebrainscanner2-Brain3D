attribute highp vec4 vertex;
attribute mediump vec3 normal;
attribute highp vec4 a_color;
uniform mediump mat4 matrix;

varying mediump vec4 v_Color;
varying mediump vec3 v_Normal;
varying mediump float z;

void main(void)
{
    v_Color = 2.0*a_color;
    v_Normal = vec3(matrix * vec4(normal, 0.0));
    gl_Position = matrix * vertex;
    z = gl_Position.z;
}
