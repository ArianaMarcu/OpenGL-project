#version 410 core
in vec3 textureCoordinates;
out vec4 color;
uniform samplerCube skybox;

void main()
{
 color = texture(skybox, textureCoordinates);
float fogFactor = 0.5f;
vec4 fogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
color = mix(fogColor, color, fogFactor);
}