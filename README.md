RealTimeSkinRendering
===============
This is an implementation of the NVIDIA's demo of real-time skin rendering

Install
---------------
This program uses make for the build.
Open a terminal and type:
...
    make
...
this should generate a binary file.

Usage
---------------
Open a terminal and type
...
    skinrenderer <path_to_file>
...
where the argument is the path to the 3D model and it's textures

TODO
---------------
- [ ] Implement base classes of the rendereing engine
- [ ] Implement .obj parser and loader
- [ ] Implement skin shader
