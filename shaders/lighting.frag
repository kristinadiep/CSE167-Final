#version 330 core

in vec4 position; // raw position in the model coord
in vec3 normal;   // raw normal in the model coord

uniform mat4 modelview; // from model coord to eye coord
uniform mat4 view;      // from world coord to eye coord

// Material parameters
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emision;
uniform float shininess;

// Light source parameters
const int maximal_allowed_lights = 10;
uniform bool enablelighting;
uniform int nlights;
uniform vec4 lightpositions[ maximal_allowed_lights ];
uniform vec4 lightcolors[ maximal_allowed_lights ];

// Output the frag color
out vec4 fragColor;


void main (void){
    if (!enablelighting){
        // Default normal coloring (you don't need to modify anything here)
        vec3 N = normalize(normal);
        fragColor = vec4(0.5f*N + 0.5f , 1.0f);
    } else {
        
        // HW3: You will compute the lighting here.
        vec4 fragColorTemp;
        mat4 model = inverse(view) * modelview;
        vec4 positionWorld = model * position;
        vec3 normalWorld = normalize(inverse(transpose(mat3(model[0][0], model[0][1], model[0][2], model[1][0], model[1][1], model[1][2], model[2][0], model[2][1], model[2][2]))) * normal);
        mat4 cameraTransform = inverse(view);
        vec3 cameraPos = vec3(cameraTransform[3][0], cameraTransform[3][1], cameraTransform[3][2]);
        vec3 modelToCam = normalize(cameraPos - vec3(positionWorld));

        for (int i = 0; i < nlights; i++) {
            vec3 lightDir = normalize((positionWorld.w * vec3(lightpositions[i].x, lightpositions[i].y, lightpositions[i].z)) - (lightpositions[i].w * vec3(positionWorld.x, positionWorld.y, positionWorld.z)));
            vec3 halfway = normalize(modelToCam + lightDir);
            vec4 diffuseColor = diffuse * max(dot(normalWorld, lightDir), 0);
            vec4 specularColor = specular * pow(max(dot(normalWorld, halfway), 0), shininess); 
            fragColorTemp += (ambient + diffuseColor + specularColor) * lightcolors[i];
        }

        fragColor = emision + fragColorTemp;
        
        if (positionWorld.w == 0) {
            fragColor = vec4(1, 0, 0, 0);
        }
    }
}
