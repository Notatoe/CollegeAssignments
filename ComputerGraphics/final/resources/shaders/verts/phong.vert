#version 300 es // Used ES 3.0

// Position of vertexes and the vertex normals
in vec3 aVertexPosition;
in vec3 aVertexNormal;
in vec2 aVertexTexCoord;

// output for the normalized vertex normals, 
out vec3 normals;
out vec3 vPosition;
out vec3 lightDirection;
out vec4 textureCoords;

// Kept these from an example since it seems to require them
uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModelMatrix;
uniform vec3 cameraPos;

uniform sampler2D image;

void main() {
  gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aVertexPosition, 1.0);
  
  // Gets the positions of vertexes in relation to the model view matrix
  vPosition = vec3(uModelViewMatrix * vec4(aVertexPosition, 1.0));

  // Gets the normals in relation to the model matrix
  normals = normalize(vec3(aVertexNormal) * -mat3(uModelMatrix));

  // Calculates the light from the direction of the camera
  lightDirection = -normalize(cameraPos - vPosition);

  textureCoords = texture(image, aVertexTexCoord);
}