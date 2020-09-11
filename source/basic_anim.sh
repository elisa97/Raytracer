#! /bin/bash

cd ../build
make
clear
cap=3;
i=0;
file="../source/scene_test.sdf"
ch=5

while [ $i -le $cap ]
do
  #navigatig to the sdf
  new_ch=$(($i * $ch))
  sed -i 's/transform eye translate.*/transform eye translate 0 0 '$new_ch'/' $file
  echo 'rendering' $i ' from ' $cap
  ./source/scene_load_test
  if [ $i -ge 1000 ]; then
    name="frame"$i".png"
    convert test1.ppm $name
  elif [ $i -ge 100 ]; then
    name="frame0"$i".png"
    convert test1.ppm $name
  elif [ $i -ge 10 ]; then
    name="frame00"$i".png"
    convert test1.ppm $name
  else
    name="frame000"$i".png"
    convert test1.ppm $name
  fi
  ((i++))
done

mkdir anim
mv frame*.png anim
cd anim 
ffmpeg -r 24 -i 'frame%04d.png' anim_$cap.mp4