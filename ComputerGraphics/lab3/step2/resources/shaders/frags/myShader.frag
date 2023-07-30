#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// vec3 that holds the normalized values of the vertex normals
in vec3 outColor;

// output that colors the object
out vec4 fragColor;

void main() {
  fragColor = vec4(abs(outColor), 1.0);
}