#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec2 that holds the texture coordinates 
in vec2 textureCoords;

// output that colors the object
out vec4 fragColor;

// Reads in the image
uniform sampler2D image;

void main() {
  // Inserts the texture using the imported image and texture coordinates
  fragColor = texture(image, textureCoords);
  if(fragColor.a < 0.1) {discard;};
}