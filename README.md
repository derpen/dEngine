# dEngine

Under HEAVY development (an hour a day work, when I feel like working on it)

A game engine, by derpen (me :3)

Libraries used:
* OpenGL 4.6
* gcc 13.2.1-13

## Setting up environment: 

Developed in Artix linux.

`sudo pacman -Sy glfw-x11 mesa-utils glew glm`

Nvidia drivers. If you use amd/intel, [here.](https://wiki.archlinux.org/title/OpenGL)

`yay -S nvidia-390xx-dkms nvidia-390xx-utils`

Copy `include` folder to your include folder.
`sudo cp -R include/* /usr/include/*`

## Resources:

https://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/#introduction

https://github.com/opengl-tutorials/ogl

https://learnopengl.com

https://medium.com/geekculture/a-beginners-guide-to-setup-opengl-in-linux-debian-2bfe02ccd1e

Unironically, ChatGPT is much better at debugging for c++ and OpenGL than just simply googling/duck-duck-go-ing. Lmao

## Build

Build with:
`make`

Run with:
`make run`

Clean with
`make clean`

Personally, I would do all 3 at once (for now)
`make && make run && make clean`
