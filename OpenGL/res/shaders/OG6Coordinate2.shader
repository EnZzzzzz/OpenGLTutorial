#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    //FragColor = texture(ourTexture2, TexCoord);
    FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}