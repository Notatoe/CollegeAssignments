My final includes the following

5 Objects:
- Skybox
- Glass Box (on top of the podium with minecraft glass textures)
- Podium (the stone brick base)
- Diamond (diamond shaped object inside the glass box)
- Sphere (sphere hovering above the display case)

5 Shaders:
- Each Object has it's own vertex and fragment shader associated with it

3 Effects (maybe more depending on what is considered one):
- Bump map on the podium (a little hard to see since the grooves between bricks is kinda shallow but it is there)
- Fog on the podium and diamond (Whenever the z value for camera position exceeds 10 or -10 they start to be inveloped in fog)
- Enviroment map on the sphere reflecting the skybox (more easily viewable when y is 2 on both camera position on camera focus)

These may or may not be considered effects but I thought I would list them anyways:
- Cube map on the glass box (prints the minecraft glass texture on the box on top of the podium)
- Skybox covering the whole scene
- Phong shader on the diamond (I don't think this is an effect, but someone claimed it was during the final project demonstrations so I thought I would just add it)