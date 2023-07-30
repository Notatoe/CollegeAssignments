#version 300 es // Used ES 3.0

// aVertexPosition helps with positioning and aVertexTexCoord is used for texture coordinates
in vec3 aVertexPosition;
in vec3 aVertexNormal;

// output for the texture coordinates so that they are usable in the fragment shader
out vec3 positions;
out vec3 normals;

// Three uniforms matrixes that are needed to apply a cubemap to a sphere
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);

  // Gets the vertex positions in relation to the model matrix
  positions = vec3(uModelMatrix) * aVertexPosition;
  
  // Gets the normals in relation to the model matrix
  normals = mat3(uModelMatrix) * aVertexNormal;
}