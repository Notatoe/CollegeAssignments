#version 300 es // Used ES 3.0

// Don't quite know what this does yet, but it is needed
precision mediump float;

// positions and normals in relation to the model matrix
in vec3 positions;
in vec3 normals;
in vec3 tangents;

// output that colors the object
out vec4 fragColor;

// camera position
uniform vec3 cameraPos;

// Reads in the image
uniform samplerCube cubemap;

void main() {
  // normalizes the normal values
  vec3 normal = normalize(normals);

  // Gets the direction the object is being looked at from the camera
  vec3 viewDirection = normalize(positions - cameraPos);

  // Inserts the texture using the imported image and texture coordinates
  fragColor = vec4(abs(tangents), 1.0);
}