Real Time Skin Rendering
===============
This is an implementation of the NVIDIA's demo of real-time skin rendering

Install
---------------
This program uses make for the build.
Open a terminal and type:

    git clone https://github.com/tlgimenes/RealTimeSkinRendering.git
    cd RealTimeSkinRendering
    mkdir Release
    cd Release
    cmake -DCMAKE_BUILD_TYPE="Release" ../ 
    make

this should generate a binary file.

Usage
---------------
Open a terminal and type

    skinrenderer -p <path_to_file>

where the argument is the path to the 3D model and it's textures. If you want
more options, type 

    skinrenderer -h

TODO
---------------
- [x] Implement base classes of the rendereing engine
- [ ] Implement .obj parser and loader
- [ ] Implement skin shader
