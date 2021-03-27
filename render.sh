#! /bin/bash

if [ -z $1 ]; then
    read -p '> specify the file in source/ that you want to render ' input
else 
    input=$1
fi

if [ ! -d "build/" ]; then
  echo '> build directory missing; running setup'
  ./setup.sh
fi

cd source

if [ -f $input ]; then
    if [ -x $input ]; then
        read -p '> do you want to execute '$input'?[y/N]' decision
        case $decision in 
        [Yy]* )
            ./$input
        esac
    else
        echo '> rendering '$input
        ../build/source/load_scene $input
        ppm=`awk '/^render/ {print $3}' $input`
        png=${ppm%.ppm}'.png'
        cd ../build
        convert $ppm $png
        echo '> file saved as build/'$png 
    fi
else
    echo 'the file does not exist, please check the spelling'
fi