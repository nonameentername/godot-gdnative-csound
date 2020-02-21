godot-gdnative-csound
=====================

Godot gdnative csound library to allow playing music using csound.

How to Install
--------------

Install system dependencies for Ubuntu:

    apt install libcsnd-dev

Install system dependencies for OSX:

    brew install csound


Build
-----

Initialize git submodules:

    git submodule update --init --recursive

Compile godot-cpp library:

    make godot-cpp

Compile gdnative library:

    make
