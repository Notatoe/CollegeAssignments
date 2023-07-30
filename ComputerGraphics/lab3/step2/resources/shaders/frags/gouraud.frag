#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec4 that holds the value of the coloration of the object
in vec4 outColor;
in vec4 Ambient;
in vec4 Diffuse;
in vec4 specularTerm;
in vec3 lightDirection;
in vec3 normal;

// output that colors the object
out vec4 fragColor;

void main() {
  // Removes all fragments with an opacity less than 0.1
  if(Diffuse.a < 0.1){
    discard;
  };

  vec4 diffuseTerm = Diffuse * max(dot(normal, lightDirection), 0.0);

  // Sets the fragment color
  fragColor = Ambient + diffuseTerm + specularTerm;
}