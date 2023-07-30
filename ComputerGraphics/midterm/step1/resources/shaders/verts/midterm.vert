#version 300 es

// My data's inputs
in vec3 aVertexPosition;
in vec3 aTangents;
in vec3 aBitangents;
in vec2 aVertexTexCoord;
in vec3 aVertexNormal;

// My uniform values that will be used
uniform mat4 uModelMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform vec3 cameraPos;

out vec2 VertexTexCoords;
out vec3 TanLightPosition;
out vec3 TanViewPosition; 
out vec3 TanFragPosition; 

void main(void)
{
    gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);

    // Imports aVertexTexCoords to the fragment shader
    VertexTexCoords = aVertexTexCoord;

    // Creates the normal matrix
    mat3 normalMatrix = transpose(inverse(mat3(uModelMatrix)));

    // Sets up tbn as well as all of the values within it
    vec3 t = normalize(normalMatrix * aTangents);
    vec3 n = normalize(normalMatrix * aVertexNormal);
    vec3 b = normalize(normalMatrix * aBitangents);
    mat3 tbn = transpose(mat3(t, b, n));

    // Performs calculations to get positions based on the tangent and bitangent values
    TanLightPosition = tbn * cameraPos;
    TanViewPosition = tbn * cameraPos;
    TanFragPosition = tbn * vec3(uModelMatrix * vec4(aVertexPosition, 1.0));
 
    
}