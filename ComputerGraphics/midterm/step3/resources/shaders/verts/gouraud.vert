#version 300 es // Used ES 3.0

// Position of vertexes and the vertex normals
in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec2 aVertexTexCoord;

// output for the normalized vertex normals, 
out vec4 outColor;
out vec4 Ambient;
out vec4 diffuseTerm;
out vec4 specularTerm;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;
uniform vec3 cameraPos;

uniform sampler2D image;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  
  // Gets the positions of vertexes in relation to the model view matrix
  vec3 vPosition = vec3(uModelViewMatrix * vec4(aVertexPosition, 1.0));

  // Gets the normals in relation to the model matrix
  vec3 normals = normalize(vec3(aVertexNormal) * -mat3(uModelMatrix));

  // Calculates the light from the direction of the camera
  vec3 lightDirection = -normalize(cameraPos - vPosition);

  vec4 textures = texture(image, aVertexTexCoord);

  // Material Values: Copper except for diffuse since it is changed for step 2
  Ambient = vec4(0.19125, 0.0735, 0.0225, 1.0);
  vec4 Diffuse = textures;
  vec4 Specular = vec4(0.256777, 0.137622, 0.086014, 1.0);
  float Shininess = 12.6;

  // Makes sure the normal values normalizes
  vec3 normal = normalize(normals);
  
  // Calculates material terms for the overall color of the object
  diffuseTerm = Diffuse * max(dot(normal, lightDirection), 0.0);
  vec3 viewDirection = normalize(-vPosition);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(reflectionDirection, viewDirection), 0.0), Shininess);
  specularTerm = Specular * specularFactor;
}