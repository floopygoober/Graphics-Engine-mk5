#version 410
layout (location = 0) in  vec3 vVertex;
layout (location = 1) in  vec3 vNormal;


out vec3 vertNormal;
out vec3 vertDir; 
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform float time;
uniform sampler3D Noise;


void main() {
	
	vertNormal = normalMatrix * vNormal; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vec4(vVertex, 1.0)); /// Creates the vertex position (-eyeDir) 
	vertDir = normalize(vertPos);
	
	//vec3 noiseVert = (Noise, (vVertex * time));
	///how it works ^ vs how it used to be
	vec4 noiseVert = texture(Noise, (vVertex * time));
	
	vec3 newV = vVertex + (vertNormal + noiseVert.xyz);
	
	//vec3 newVec = vVertex + (vNormal * time);
	
	//newV = vVertex + (vec4(vertNormal, 1) * vec4(10, 10, 10, 10));
	
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(newV, 1.0); 


}
