attribute vec2 vPosition;
attribute vec3 vColor;
out vec3 pass_Color;
uniform mat4 mvMatrix;

void main()
{
	    gl_Position =  vec4(vPosition, 0.0, 1.0)*mvMatrix;
	    pass_Color = vColor;
}
