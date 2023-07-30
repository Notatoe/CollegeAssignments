#version 300 es

precision mediump float;

// The texture coordinates and the tangent and bitangent calculated positions
in vec2 VertexTexCoords;
in vec3 TanLightPosition;
in vec3 TanViewPosition;
in vec3 TanFragPosition;

// The two imported textures that will be applied to create a lighting effect
uniform sampler2D normalMap;
uniform sampler2D diffuseMap;
uniform float fog;

out vec4 fragColor;

void main()
{
    // Gets the normal within tangent space
    vec3 tanNormal = (normalize(texture(normalMap, VertexTexCoords).rgb)) * 2.0 - 1.0;

    // Sets up an initial texture calculation with diffuseMap and texture coords
    vec3 Diffuse = texture(diffuseMap, VertexTexCoords).rgb;

    // Sets up the ambient
    vec3 Ambient = 0.1 * Diffuse;
    
    // Sets up the direction of light and view as well as updates diffuse
    vec3 lightDirection = normalize(TanLightPosition - TanFragPosition);
    vec3 viewDirection = normalize(TanViewPosition - TanFragPosition);
    Diffuse = max(dot(lightDirection, tanNormal), 0.0) * Diffuse;


    // Adds the two directions together and normalizes it
    vec3 direction = normalize(lightDirection + viewDirection);

    // Sets up specular
    vec3 Specular = vec3(0.2) * pow(max(dot(tanNormal, direction), 0.0), 32.0);
    
    vec4 fogColor = vec4(0.8, 0.9, 1, 1);

    // Calculates the final colors of the object with normal mapped lights
    fragColor = mix(vec4(Ambient + Diffuse + Specular, 1.0), fogColor, fog);
}