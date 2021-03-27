<h1 align="center">a C++ Raytracer</h1>  

![anim](misc/anim.webp)


a very compressed webp to give an idea of whats possible with a bit of scripting, a nicer mp4 can be found in `misc/`

setup can be done via the `setup.sh` but isn't really necessary since the render-script `render.sh` checks if setup was run and runs it if it wasn't.
`render.sh` takes the filename of the animation/scene in the `source` directory as argument and renders it if it finds a file with that name. when finished it converts the output `.ppm` to `.png` and shows where it is saved.

the initial compiling could take some time and the rendering will take a _very_ long time (for the animation at least), especially if you render it with a higher resolution/aa which can be specified in the `.sdf` files along with the materials you want to use.

of course you can also render custom scenes you created in the `.sdf` format and alter `source/scene_load.cpp` to load your scene. it supports refelection, refraction, phong-shading and transprarency. objects can be shperes or cubes which can be transformed/translated.