#version 410
in  vec3 vertNormal;
in  vec3 vertDir;
out vec4 fragColor;

in vec3 color;


uniform samplerCube skybox;

void main() 
{
    vec3 Reflect = reflect(vertDir, vertNormal);
    vec4 fragColorReflect = texture(skybox, Reflect);

    float ratio = 1.00 / 1.52;
    vec3 Refract = refract(vertDir, vertNormal, ratio);
    vec4 fragColorRefract = texture(skybox, Refract);


    fragColor = mix(fragColorReflect, fragColorRefract, dot(-vertDir, vertNormal));

}
