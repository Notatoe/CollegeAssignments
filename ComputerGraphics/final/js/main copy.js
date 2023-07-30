// Ideally, we like to avoid global vars, a GL context lives as long as the window does
// So this is a case where it is understandable to have it in global space.
var gl = null;
// The rest is here simply because it made debugging easier...
var myShader = null;
// Does not work with myDrawable as a global, so I removed it :)
var myDrawableInitialized = null;
var modelViewMatrix = null;
var projectionMatrix = null;
var globalTime = 0.0;
var parsedData = null;
var modelMatrix = null;

var cameraPos = null;

// Array that carries the 10 initialized objects
var Objects = [];

// scaling vector held as a global
var scalingVector = [0,0,0];

function main() {
  const canvas = document.getElementById('glCanvas');
  // Initialize the GL context
  gl = canvas.getContext('webgl2');

  // Only continue if WebGL is available and working
  if (gl === null) {
    alert('Unable to initialize WebGL2. Contact the TA.');
    return;
  }

  // Set clear color to whatever color this is and fully opaque
  gl.clearColor(0.7, 0.7, 0.9, 1.0);
  // Clear the depth buffer
  gl.clearDepth(1.0);
  // Enable the depth function to draw nearer things over farther things
  gl.depthFunc(gl.LEQUAL);
  gl.enable(gl.DEPTH_TEST);

  // Draw the scene repeatedly
  let then = 0.0;
  function render(now) {
    now *= 0.001;  // convert to seconds
    const deltaTime = now - then;
    then = now;

    drawScene(deltaTime);

    requestAnimationFrame(render);
  }
  requestAnimationFrame(render);

  // The Projection matrix rarely needs updated.
  // Uncommonly, it is only modified in wacky sequences ("drunk" camera effect in GTAV)
  // or an artificial "zoom" using FOV (ARMA3)
  // Typically it is only updated when the viewport changes aspect ratio.
  // So, set it up here once since we won't let the viewport/canvas resize.
  const FOV = degreesToRadians(60);
  const aspectRatio = gl.canvas.clientWidth / gl.canvas.clientHeight;
  const zNear = 0.1;
  const zFar  = 100.0;
  projectionMatrix = glMatrix.mat4.create();
  glMatrix.mat4.perspective(projectionMatrix,
                   FOV,
                   aspectRatio,
                   zNear,
                   zFar);

  // Setup Controls
  setupUI();

  // Right now, in draw, the scene will not render until the drawable is prepared
  // this allows us to acynchronously load content. If you are not familiar with async
  // that is a-okay! This link below should explain more on that topic:
  // https://blog.bitsrc.io/understanding-asynchronous-javascript-the-event-loop-74cd408419ff
  setupScene();
}

function setupUI() {
  // in index.html we need to setup some callback functions for the sliders
  // right now just have them report the values beside the slider.
  let sliders = ['cam', 'look'];
  let dims = ['X', 'Y', 'Z'];
  // for cam and look UI..
  sliders.forEach(controlType => {
    // for x, y, z control slider...
    dims.forEach(dimension => {
      let slideID = `${controlType}${dimension}`;
      console.log(`Setting up control for ${slideID}`);
      let slider = document.getElementById(slideID);
      let sliderVal = document.getElementById(`${slideID}Val`);
      // These are called "callback functions", essentially when the input
      // value for the slider or the field beside the slider change,
      // run the code we supply here!
      slider.oninput = () => {
        let newVal = slider.value;
        sliderVal.value = newVal;
      };
      sliderVal.oninput = () => {
        let newVal = sliderVal.value;
        slider.value = newVal;
      };
    });
  });
}

// Async as it loads resources over the network.
async function setupScene() {
  let objData = await loadNetworkResourceAsText('resources/models/textureCube.obj');
  let vertSource = await loadNetworkResourceAsText('resources/shaders/verts/image.vert');
  let fragSource = await loadNetworkResourceAsText('resources/shaders/frags/image.frag');

  let objData2 = await loadNetworkResourceAsText('resources/models/diamond.obj');
  let vertSource2 = await loadNetworkResourceAsText('resources/shaders/verts/diamond.vert');
  let fragSource2 = await loadNetworkResourceAsText('resources/shaders/frags/diamond.frag');

  let objData3 = await loadNetworkResourceAsText('resources/models/podium.obj');
  let vertSource3 = await loadNetworkResourceAsText('resources/shaders/verts/diamond.vert');
  let fragSource3 = await loadNetworkResourceAsText('resources/shaders/frags/podium.frag');

  let objData4 = await loadNetworkResourceAsText('resources/models/skybox.obj');
  let vertSource4 = await loadNetworkResourceAsText('resources/shaders/verts/skybox.vert');
  let fragSource4 = await loadNetworkResourceAsText('resources/shaders/frags/skybox.frag');
  
  // Runs through InitializeMyObject 10 times and pushes the initialized object into Objects so that there are 10 objects
  Objects.push(initializeMyObject(vertSource, fragSource, objData));
  Objects.push(initializeMyObject(vertSource2, fragSource2, objData2));
  Objects.push(initializeMyObject(vertSource3, fragSource3, objData3));
  Objects.push(initializeMyObject(vertSource4, fragSource4, objData4));
}

function drawScene(deltaTime) {
  globalTime += deltaTime;
  // Clear the color buffer with specified clear color
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  // j value is to help with spacing of the objects
  let j = 0

  for(let i = 0; i < 4; i++)
  { 
    modelMatrix = glMatrix.mat4.create();

    // Changed the position to involve this math to rotate around the orgin
    let objectWorldPos = [0.0, 0.0, 0.0];
    if(i == 1)
    {
      objectWorldPos = [0.0, -0.6, 0.0];
    }
    if(i == 2)
    {
      objectWorldPos = [0.0, -1.99, 0.0];
    }
    
    // Updates the j value for spacing

    let rotationAxis = [1.0, 1.0, 0.0];
    glMatrix.mat4.translate(modelMatrix, modelMatrix, objectWorldPos);
    glMatrix.mat4.rotate(modelMatrix,
                          modelMatrix,
                          0,
                          rotationAxis
                          );
    
    // Sets the scale for the model using the scaling vector
    if(i == 1)
    {
      glMatrix.mat4.scale(modelMatrix, modelMatrix, scalingVector)
    }

    let viewMatrix = glMatrix.mat4.create();

    // Step 0 changes
    cameraPos = [document.getElementById("camXVal").value, document.getElementById("camYVal").value, document.getElementById("camZVal").value];
    let cameraFocus = [document.getElementById("lookXVal").value, document.getElementById("lookYVal").value, document.getElementById("lookZVal").value];

    glMatrix.mat4.lookAt(viewMatrix,
                        cameraPos,
                        cameraFocus,
                        [0.0, 1.0, 0.0]
                        );
    
    modelViewMatrix = glMatrix.mat4.create();
    glMatrix.mat4.mul(modelViewMatrix, viewMatrix, modelMatrix);

    // Draws an object from Objects instead of from myDrawable
    if(myDrawableInitialized){
      Objects[i].draw();
    }
  }
}

function initializeMyObject(vertSource, fragSource, objData) {
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

  var texture = gl.createTexture();
  var image = new Image();
  image.src = "imagefiles/glass.png";

  // Puts the image onto the texture
  image.addEventListener('load', function() {
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA,gl.UNSIGNED_BYTE, image);
    gl.generateMipmap(gl.TEXTURE_2D);
  });

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

// After all the DOM has loaded, we can run the main function.
window.onload = main;