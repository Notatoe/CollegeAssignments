#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec3 that holds the normalized values of the vertex normals
in vec3 normals;
in vec3 vPosition;
in vec3 lightDirection;

// output that colors the object
out vec4 fragColor;

uniform float fog;

void main() {
  // Material Values: Ruby
  vec4 Ambient = vec4(0.1745, 0.01175, 0.01175, 0.55);
  vec4 Diffuse = vec4(0.61424, 0.04136, 0.04136, 0.55);
  vec4 Specular = vec4(0.727811, 0.626959, 0.626959, 0.55);
  float Shininess = 76.8;

  // Makes sure the normal values normalizes
  vec3 normal = normalize(normals);
  
  // Calculates material terms for the overall color of the object
  vec4 diffuseTerm = Diffuse * max(dot(normal, lightDirection), 0.0);
  vec3 viewDirection = normalize(-vPosition);
  vec3 reflectionDirection = reflect(-lightDirection, normal);
  float specularFactor = pow(max(dot(reflectionDirection, viewDirection), 0.0), Shininess);
  vec4 specularTerm = Specular * specularFactor;

  vec4 fogColor = vec4(0.8, 0.9, 1, 1);

  // Sets the fragment color
  fragColor = mix(Ambient + diffuseTerm + specularTerm, fogColor, fog);
}