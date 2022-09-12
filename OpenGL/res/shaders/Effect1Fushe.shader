#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
out float circle; // 画出这个圆看看什么情况

uniform mat4 u_MVP;

float sdCircle(vec2 p, float r)
{
    return length(p) - r;
}

void main()
{
    vec4 pos = u_MVP * vec4(aPos, 1.0);

    float cir = sdCircle(pos.xy, 0.5);
    pos.z -= 0.5;

    gl_Position = pos;
    ourColor = aColor;
    TexCoord = aTexCoord;
    circle = cir;
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float circle;

uniform sampler2D ourTexture;

void main()
{
    vec3 color = vec3(circle);
    FragColor = vec4(color, 1.0);
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}