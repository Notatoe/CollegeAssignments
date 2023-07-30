#version 300 es // Used ES 3.0

// aVertexPosition helps with positioning and aVertexNormal is needed for coloring the sphere rainbow
in vec3 aVertexPosition;
in vec3 aVertexNormal;

// output for the normalized vertex normals
out vec3 outColor;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  outColor = vec3(normalize(aVertexNormal));
}