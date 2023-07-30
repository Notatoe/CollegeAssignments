#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec4 that holds the value of the coloration of the object
in vec4 outColor;

// output that colors the object
out vec4 fragColor;

void main() {
  // Sets the fragment color
  fragColor = outColor;
}