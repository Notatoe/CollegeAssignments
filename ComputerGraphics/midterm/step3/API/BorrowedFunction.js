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