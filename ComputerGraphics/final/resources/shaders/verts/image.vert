#version 300 es // Used ES 3.0

// aVertexPosition helps with positioning and aVertexTexCoord is used for texture coordinates
in vec3 aVertexPosition;
in vec2 aVertexTexCoord;

// output for the texture coordinates so that they are usable in the fragment shader
out vec2 textureCoords;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  
  textureCoords = aVertexTexCoord;
}