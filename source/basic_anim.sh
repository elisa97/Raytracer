#! /bin/bash

#path to the sdf
file="../source/scene_test.sdf"

cap=120
i=0
ch=1

cd ../build
make
clear

if [ ! -d "$anim" ]; then
  echo 'created folder anim'
  mkdir anim
fi

while [ $i -le $cap ]
do
  new_ch=$(($i * $ch))

  #rewriting a line in the file
  sed -i 's/transform eye rotate.*/transform eye rotate '$new_ch' 0 1 0/' $file

  #rendering the file
  echo 'rendering' $i ' from ' $cap
  ./source/scene_load_test

  #padding for ffmpeg
  convert test1.ppm 'anim/frame'`printf "%04d" $i`'.png'
  
  ((i++))
done

#generating the video
ffmpeg -r 30 -i anim/'frame%04d.png' anim_$cap.mp4

#cleanup if needed
#rm anim