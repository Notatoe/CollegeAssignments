// Function takes in vertexData and textureData to calculate tangents and bitangents
function GetTangents(vertexData, textureData)
{
    var tangents = [];
    var bitangents = [];
    for(let i = 0; i < vertexData.length; i += 9)
        {
        // Takes information from the 3 vertexes of the current triangle
        var vertex1x = vertexData[i];
        var vertex1y = vertexData[i + 1];
        var vertex1z = vertexData[i + 2];
        var vertex2x = vertexData[i + 3];
        var vertex2y = vertexData[i + 4];
        var vertex2z = vertexData[i + 5];
        var vertex3x = vertexData[i + 6];
        var vertex3y = vertexData[i + 7];
        var vertex3z = vertexData[i + 8];

        // Takes the information from the 3 texture coordinates of the current triangle
        var uv1x = textureData[((i * 2) / 3)];
        var uv1y = textureData[((i * 2) / 3) + 1];
        var uv2x = textureData[((i * 2) / 3) + 2];
        var uv2y = textureData[((i * 2) / 3) + 3];
        var uv3x = textureData[((i * 2) / 3) + 4];
        var uv3y = textureData[((i * 2) / 3) + 5];

        // Calculates the 2 edge x, y, and z values
        var edge1x = vertex2x - vertex1x;
        var edge1y = vertex2y - vertex1y;
        var edge1z = vertex2z - vertex1z;
        var edge2x = vertex3x - vertex1x;
        var edge2y = vertex3y - vertex1y;
        var edge2z = vertex3z - vertex1z;

        // Calculates the delta values for the texture coords
        var deltaUV1x = uv2x - uv1x;
        var deltaUV1y = uv2y - uv1y;
        var deltaUV2x = uv3x - uv1x;
        var deltaUV2y = uv3y - uv1y;

        // Calculates and puhes the tangents and bitangent values
        // Does this three times per traingle
        for(let j = 0; j < 3; j++)
        {
            var f = 1.0 / ((deltaUV1x * deltaUV2y) - (deltaUV2x * deltaUV1y));
            tangents.push((f * ((deltaUV2y * edge1x) - (deltaUV1y * edge2x))));
            tangents.push((f * ((deltaUV2y * edge1y) - (deltaUV1y * edge2y))));
            tangents.push((f * ((deltaUV2y * edge1z) - (deltaUV1y * edge2z))));

            bitangents.push((f * ((-deltaUV2x * edge1x) + (deltaUV1x * edge2x))));
            bitangents.push((f * ((-deltaUV2x * edge1y) + (deltaUV1x * edge2y))));
            bitangents.push((f * ((-deltaUV2x * edge1z) + (deltaUV1x * edge2z))));
        }
    }

    // To condense tangents and bitangents into one function, I returned an array with tangents and bitangents held in its two indexes
    var both = [tangents, bitangents]
    return both;
}