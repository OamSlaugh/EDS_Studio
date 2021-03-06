#version 330

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

in vec2 a_Vertex;
in vec3 b_Color;
in vec2 a_TexCoord0;
out vec4 color;
out vec4 position;
out vec2 texCoord0;

void main(void)
{
   color = vec4(b_Color, 1.0);
   vec4 pos = modelview_matrix * vec4(a_Vertex,0.0, 1.0);
   gl_Position = projection_matrix * pos;
   texCoord0 = a_TexCoord0;
}
