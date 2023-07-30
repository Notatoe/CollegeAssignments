#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec2 that holds the texture coordinates 
in vec3 texturePosition;

// output that colors the object
out vec4 fragColor;

// Reads in the image
uniform samplerCube skybox;

void main() {
  // Inserts the texture using the imported images and texture position
  fragColor = texture(skybox, texturePosition);
}