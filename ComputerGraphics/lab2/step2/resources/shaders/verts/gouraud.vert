#version 300 es // Used ES 3.0

// Position of vertexes and the vertex normals
in vec3 aVertexPosition;
in vec3 aVertexNormal;

// output for the normalized vertex normals, 
out vec4 outColor;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;
uniform vec3 cameraPos;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  
  // Gets the positions of vertexes in relation to the model view matrix
  vec3 vPosition = vec3(uModelViewMatrix * vec4(aVertexPosition, 1.0));

  // Gets the normals in relation to the model matrix
  vec3 normals = normalize(vec3(aVertexNormal) * -mat3(uModelMatrix));

  // Calculates the light from the direction of the camera
  vec3 lightDirection = -normalize(cameraPos - vPosition);

  // Material Values: Polished Bronze
  vec4 Ambient = vec4(0.25, 0.148, 0.06475, 1.0);
  vec4 Diffuse = vec4(0.4, 0.2368, 0.1036, 1.0);
  vec4 Specular = vec4(0.774597, 0.458561, 0.200621, 1.0);
  float Shininess = 76.8;

  // Makes sure the normal values normalizes
  vec3 normal = normalize(normals);
  
  // Calculates material terms for the overall color of the object
  vec4 diffuseTerm = Diffuse * max(dot(normal, lightDirection), 0.0);
  vec3 viewDirection = normalize(-vPosition);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(reflectionDirection, viewDirection), 0.0), Shininess);
  vec4 specularTerm = Specular * specularFactor;

  // Result of calculating how the object should be colored
  outColor = Ambient + diffuseTerm + specularTerm;
}