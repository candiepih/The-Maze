# The-Maze

The maze is a 3D game rednered from a 2D map using a technique known as raycasting. This was a technique that was popular in game develpment in thte 90s. Wolfenstein 3D was one of the games that used this technique. This project is an attempt to obtain some knowledge and experience on the multimedia title development process using [SDL - Simple DirectMedia Layer](https://www.libsdl.org/) library.

`Simple DirectMedia Layer`(*SDL*) is a cross-platform software development library designed to provide a hardware abstraction layer for computer multimedia hardware components, to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. 

More about sdl [from sdl webpage here](https://www.libsdl.org/)

`Ray-casting` is a technique that transform a limited form of data (a very simplified map or floor plan) into a 3D projection by tracing rays from the view point into the viewing volume (LaMothe 942).

![figure1](https://user-images.githubusercontent.com/44834632/138761695-32039d06-5111-4d56-b8f8-1a18d5fbb239.gif)

image from https://permadi.com/

# Compilling

This project makes use of `gcc` and `make` for the compilation process.

### Windows

Ensure you have gcc, and make(*Can install using chocolatey*)

run `make`

### Linux

First make sure SDL is installed. If you haven't install SDL by running `make linux_install`.

run `make linux` to compile.

### Mac

Ensure sdl is installed.

run `make mac` (*Haven't tested it yet on Mac environment*)

# Controls

`W` - Moving forward
`S` - Moving backward
`A` - Look left
`D` - Look right
 `Mouse move left/right` - look left or right
 `M` - Turn off map visibility. The 2D map won't be visible on clicking
 `N` - Turn on map visibility. The 2D map will be visible again if it wasn't
 
### Texture source

Weapon

https://www.seekpng.com/idown/u2w7u2t4i1y3a9y3_call-of-duty-guns-firearms-gun-weapons-coat/
