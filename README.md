# Introduction
This is my first attempt to create my own text editor. The biggest challenge was figuring out how to store the text document in memory. I thought I can use an array, but that has horrible performance in insertion and deletion.

There are some good data structures for that problem:
- [Rope](https://en.wikipedia.org/wiki/Rope_(data_structure))
- [Gap buffer](https://en.wikipedia.org/wiki/Gap_buffer) _`which I used decided to use`_
- [Piece table](https://en.wikipedia.org/wiki/Piece_table)

[![demo video](https://img.youtube.com/vi/z80M3mUxKdM/maxresdefault.jpg)](https://youtu.be/z80M3mUxKdM)


# Build & Run
## Linux
-   Install sub-modules in lib folder
    - [FreeType](https://freetype.org)
    - [Glad](https://glad.dav1d.de/)
    - [GLFW](https://github.com/glfw/glfw)
    - [GLM](https://github.com/g-truc/glm)
-   Run these commands
```bash
    make libs # Builds all the libraries
    make all  # Build text editor
    ./debug/program ${file_name}
```