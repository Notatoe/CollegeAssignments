#version 300 es // Used ES 3.0

// aVertexPosition helps with positioning
in vec3 aVertexPosition;

// output for the position coordinates so that they are usable in the fragment shader
out vec3 texturePosition;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  
  texturePosition = aVertexPosition;
}