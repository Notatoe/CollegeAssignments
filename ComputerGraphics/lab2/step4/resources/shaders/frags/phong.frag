#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec3 that holds the normalized values of the vertex normals
in vec3 normals;
in vec3 vPosition;
in vec3 lightDirection;
in float height;

// output that colors the object
out vec4 fragColor;

void main() {
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

  // Removes the red from fragColor and adds modulation of the red component by height
  fragColor = vec4(Ambient.rgb, 1.0) + diffuseTerm + specularTerm;
  fragColor.r *= height;
}