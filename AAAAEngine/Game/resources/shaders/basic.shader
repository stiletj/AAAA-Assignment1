#shader vertex
#version 330 core
 
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord; 

out vec2 v_TexCoord; 
out vec3 Normal0;
out vec3 LocalPos0;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord; 
    Normal0 = normal;
    LocalPos0.x = position.x;
    LocalPos0.y = position.y;
    LocalPos0.z = position.z;
};
 
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord; 

uniform sampler2D u_Texture; 

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
};