#version 410
in vec3 uvwCoords;
out vec4 fragColor;

uniform samplerCube SkyboxTexture;

void main() { 
	fragColor = texture(SkyboxTexture, uvwCoords);
} 

