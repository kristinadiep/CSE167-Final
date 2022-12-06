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
        fragColor = vec4(0.5f*N + 0.5f , 2.0f);
    } else {
        
        // HW3: You will compute the lighting here.
        // fragColor == vec4( ? )

        // emision + sum(ambient
        //             + diffuse * (max of normal dot light, and 0)
        //             + specular * (max of normal dot half vector, and 0)^shininess
        // ) * lightcolors
        
        // totalLight is sum of light (material coeffs * rgb light) so far
        // currMatLight is current light source (material coeffs * rgb light)
        vec4 totalLight, currMatLight = vec4(0.0f, 0.0f, 0.0f, 1.0f);

        // calculates resultant light for each light source
        for (int i = 0; i < maximal_allowed_lights; i++) {
            // ambient constant
            currMatLight = ambient;
            // diffuse * max([normal] dot [direction to light], 0)
            vec4 lightDir = lightpositions[i] - position; // check hw hints
            currMatLight += diffuse; // transform normal first, and position first, before calculating other vecs
            // we will use the normal vector (currently in model coord)
            // and the light vector (light pos - model pos)
            // light pos is (currently in world coord)
            // model pos is (currently in model coord)
            vec4 worldModelPos = position;

            mat3 normTransform = mat3(modelview); // ? check hw hints
            vec3 worldNormalVec = normal;

            totalLight += currMatLight * lightcolors[i];
        }

        fragColor = emision + totalLight;
    }
}
