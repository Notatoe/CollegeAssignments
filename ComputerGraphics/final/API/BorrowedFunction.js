// Function taken and modified from the Khronos opengl page for loading textures
function loadTexture(src) {
    // Sets up the texture
    var texture = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture);
  
    // Sets up the image
    var image = new Image();
    image.onload = function() {
        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
    };
    // Assigns the path to the image
    image.src = src;
    return texture;
}

// Duplicated "initializeMyObject" function specifically for the cubemaps
function initializeMyCubemap(vertSource, fragSource, objData) {
    myShader = new ShaderProgram(vertSource, fragSource); // this class is in shader.js
    parsedData = new OBJData(objData); // this class is in obj-loader.js
    let rawData = parsedData.getFlattenedDataFromModelAtIndex(0);
  
    // Generate Buffers on the GPU using the geometry data we pull from the obj
    let vertexPositionBuffer = new VertexArrayData( // this class is in vertex-data.js
      rawData.vertices, // What is the data?
      gl.FLOAT,         // What type should WebGL treat it as?
      3                 // How many per vertex?
    );
    // Uncommented this for step 0 of lab 2
    let vertexNormalBuffer = new VertexArrayData(
      rawData.normals,
      gl.FLOAT,
      3
    );
    let vertexTexCoordBuffer = new VertexArrayData (
      rawData.uvs,
      gl.FLOAT,
      2
    );
    let vertexBarycentricBuffer = new VertexArrayData (
      rawData.barycentricCoords,
      gl.FLOAT,
      3
    );
    let tangents = new VertexArrayData (
      rawData.tangents,
      gl.FLOAT,
      3
    );
    let bitangents = new VertexArrayData (
      rawData.bitangents,
      gl.FLOAT,
      3
    );
  
    // Reads in the scaling vector from the object loader
    scalingVector = rawData.scalingVector;
  
    // console.log(rawData);
    // console.log(bitangents);
  
    /*
    For any model that is smooth (non discrete) indices should be used, but we are learning! Maybe you can get this working later?
    One indicator if a model is discrete: a vertex position has two normals.
    A cube is discrete if only 8 vertices are used, but each vertex has 3 normals (each vertex is on the corner of three faces!)
    The sphere and bunny obj models are smooth though */
    // getFlattenedDataFromModelAtIndex does not return indices, but getIndexableDataFromModelAtIndex would
    //let vertexIndexBuffer = new ElementArrayData(rawData.indices);
  
    // In order to let our shader be aware of the vertex data, we need to bind
    // these buffers to the attribute location inside of the vertex shader.
    // The attributes in the shader must have the name specified in the following object
    // or the draw call will fail, possibly silently!
    // Checkout the vertex shaders in resources/shaders/verts/* to see how the shader uses attributes.
    // Checkout the Drawable constructor and draw function to see how it tells the GPU to bind these buffers for drawing.
    let bufferMap = {
      'aVertexPosition': vertexPositionBuffer,
      'aBarycentricCoord': vertexBarycentricBuffer,
      // Incorporated vertex normals
      'aVertexNormal': vertexNormalBuffer, //-> Not working with normals, yet! The sphere has norms included, the bunny needs norms generated.
      // Pretty sure this works when the texture coords are included
      'aVertexTexCoord': vertexTexCoordBuffer, //-> Same, not working with texture coords yet.
      'aTangents': tangents,
      'aBitangents': bitangents
    };
  
    var myDrawable = new Drawable(myShader, bufferMap, null, rawData.vertices.length / 3);
  
    // Loads the 2 textures to be normal mapped to the texture cube
    //var texture = loadTexture("toy_box_assets/toy_box_normal.png");
    //var texture2 = loadTexture("toy_box_assets/toy_box_diffuse.png");
  
    var texture2 = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_CUBE_MAP, texture2);
  
    // Loads in each face for the cube map
    const faceInfos = [
      { face: gl.TEXTURE_CUBE_MAP_POSITIVE_X, picture: 'skybox/posx.jpg'},
      { face: gl.TEXTURE_CUBE_MAP_NEGATIVE_X, picture: 'skybox/negx.jpg'},
      { face: gl.TEXTURE_CUBE_MAP_POSITIVE_Y, picture: 'skybox/posy.jpg'},
      { face: gl.TEXTURE_CUBE_MAP_NEGATIVE_Y, picture: 'skybox/negy.jpg'},
      { face: gl.TEXTURE_CUBE_MAP_POSITIVE_Z, picture: 'skybox/posz.jpg'},
      { face: gl.TEXTURE_CUBE_MAP_NEGATIVE_Z, picture: 'skybox/negz.jpg'},];
  
    // Goes through each face and applies them to the cubemap
    faceInfos.forEach((faceInfo) => {
      const {face, picture} = faceInfo;
   
      // sets up each 2d image
      gl.texImage2D(face, 0, gl.RGBA, 512, 512, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);
   
      // Loads each image and places them on the cubemap
      const image = new Image();
      image.src = picture;
      image.addEventListener('load', function() {
        gl.bindTexture(gl.TEXTURE_CUBE_MAP, texture2);
        gl.texImage2D(face, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
        gl.generateMipmap(gl.TEXTURE_CUBE_MAP);
      });
    });
    
    // makes sure the cube map is loaded
    gl.generateMipmap(gl.TEXTURE_CUBE_MAP);
    gl.texParameteri(gl.TEXTURE_CUBE_MAP, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_LINEAR);
  
  
    // Checkout the drawable class' draw function. It calls a uniform setup function every time it is drawn. 
    // Put your uniforms that change per frame in this setup function.
    myDrawable.uniformLocations = myShader.getUniformLocations(['uModelViewMatrix', 'uProjectionMatrix', "uModelMatrix", "cameraPos", "normalMap", "diffuseMap"]);
    myDrawable.uniformSetup = () => {
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uProjectionMatrix,
        false,
        projectionMatrix
      );
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uModelViewMatrix,
        false,
        modelViewMatrix
      );
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uModelMatrix,
        false,
        modelMatrix
      );
      gl.uniform3fv(myDrawable.uniformLocations.cameraPos, cameraPos);
  
      // // Sets normalMap to texture 0 and diffuseMap to texture 1
      // gl.uniform1i(myDrawable.uniformLocations.normalMap, 0);
      // gl.uniform1i(myDrawable.uniformLocations.diffuseMap, 1);
  
      // // Applys the first image texture to texture0
      // gl.activeTexture(gl.TEXTURE0);
      // gl.bindTexture(gl.TEXTURE_2D, texture);
  
      // // Applys the second image texture to texture1
      // gl.activeTexture(gl.TEXTURE1);
      // gl.bindTexture(gl.TEXTURE_2D, texture2);
    };
  
    myDrawableInitialized = true;
  
    // function now returns a drawable object
    return myDrawable;
  }


// Duplicated "initializeMyObject" function specifically for the bumpmap podium object
  function initializeMyBumpmap(vertSource, fragSource, objData) {
    myShader = new ShaderProgram(vertSource, fragSource); // this class is in shader.js
    parsedData = new OBJData(objData); // this class is in obj-loader.js
    let rawData = parsedData.getFlattenedDataFromModelAtIndex(0);
  
    // Generate Buffers on the GPU using the geometry data we pull from the obj
    let vertexPositionBuffer = new VertexArrayData( // this class is in vertex-data.js
      rawData.vertices, // What is the data?
      gl.FLOAT,         // What type should WebGL treat it as?
      3                 // How many per vertex?
    );
    // Uncommented this for step 0 of lab 2
    let vertexNormalBuffer = new VertexArrayData(
      rawData.normals,
      gl.FLOAT,
      3
    );
    let vertexTexCoordBuffer = new VertexArrayData (
      rawData.uvs,
      gl.FLOAT,
      2
    );
    let vertexBarycentricBuffer = new VertexArrayData (
      rawData.barycentricCoords,
      gl.FLOAT,
      3
    );
    let tangents = new VertexArrayData (
      rawData.tangents,
      gl.FLOAT,
      3
    );
    let bitangents = new VertexArrayData (
      rawData.bitangents,
      gl.FLOAT,
      3
    );
  
    // Reads in the scaling vector from the object loader
    scalingVector = rawData.scalingVector;
  
    // console.log(rawData);
    // console.log(bitangents);
  
    /*
    For any model that is smooth (non discrete) indices should be used, but we are learning! Maybe you can get this working later?
    One indicator if a model is discrete: a vertex position has two normals.
    A cube is discrete if only 8 vertices are used, but each vertex has 3 normals (each vertex is on the corner of three faces!)
    The sphere and bunny obj models are smooth though */
    // getFlattenedDataFromModelAtIndex does not return indices, but getIndexableDataFromModelAtIndex would
    //let vertexIndexBuffer = new ElementArrayData(rawData.indices);
  
    // In order to let our shader be aware of the vertex data, we need to bind
    // these buffers to the attribute location inside of the vertex shader.
    // The attributes in the shader must have the name specified in the following object
    // or the draw call will fail, possibly silently!
    // Checkout the vertex shaders in resources/shaders/verts/* to see how the shader uses attributes.
    // Checkout the Drawable constructor and draw function to see how it tells the GPU to bind these buffers for drawing.
    let bufferMap = {
      'aVertexPosition': vertexPositionBuffer,
      'aBarycentricCoord': vertexBarycentricBuffer,
      // Incorporated vertex normals
      'aVertexNormal': vertexNormalBuffer, //-> Not working with normals, yet! The sphere has norms included, the bunny needs norms generated.
      // Pretty sure this works when the texture coords are included
      'aVertexTexCoord': vertexTexCoordBuffer, //-> Same, not working with texture coords yet.
      'aTangents': tangents,
      'aBitangents': bitangents
    };
  
    var myDrawable = new Drawable(myShader, bufferMap, null, rawData.vertices.length / 3);
  
    // Loads the 2 textures to be normal mapped to the texture cube
    var texture = loadTexture("podiumImages/brickNormal.png");
    var texture2 = loadTexture("podiumImages/marbleDiffuse.png");
  
  
    // Checkout the drawable class' draw function. It calls a uniform setup function every time it is drawn. 
    // Put your uniforms that change per frame in this setup function.
    myDrawable.uniformLocations = myShader.getUniformLocations(['uModelViewMatrix', 'uProjectionMatrix', "uModelMatrix", "cameraPos", "normalMap", "diffuseMap", "fog"]);
    myDrawable.uniformSetup = () => {
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uProjectionMatrix,
        false,
        projectionMatrix
      );
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uModelViewMatrix,
        false,
        modelViewMatrix
      );
      gl.uniformMatrix4fv(
        myDrawable.uniformLocations.uModelMatrix,
        false,
        modelMatrix
      );
      gl.uniform3fv(myDrawable.uniformLocations.cameraPos, cameraPos);
      gl.uniform1f(myDrawable.uniformLocations.fog, fog);
  
      // Sets normalMap to texture 0 and diffuseMap to texture 1
      gl.uniform1i(myDrawable.uniformLocations.normalMap, 0);
      gl.uniform1i(myDrawable.uniformLocations.diffuseMap, 1);
  
      // Applys the first image texture to texture0
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture);
  
      // Applys the second image texture to texture1
      gl.activeTexture(gl.TEXTURE1);
      gl.bindTexture(gl.TEXTURE_2D, texture2);
    };
  
    myDrawableInitialized = true;
  
    // function now returns a drawable object
    return myDrawable;
  }