#! /bin/bash

if [ ! -d "build/" ]; then
  mkdir build
  echo '> created the build directory'
fi

cd build || exit

#compiling the raytracer
cmake ..
make
clear

echo '> compiled the raytracer'
