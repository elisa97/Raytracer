#! /bin/bash

#path to the sdf
file="../source/scene_test.sdf"

cap=360
i=0
ch=1

cd ../build
make
clear

#setting up directories
if [ ! -d "frms/" ]; then
  echo 'created folder frms'
  mkdir frms
fi

if [ ! -d "anim/" ]; then
  echo 'created folder anim'
  mkdir anim
fi

#important part
while [ $i -le $cap ]
do
  new_ch=$(($i * $ch))

  #rewriting a line in the file
  sed -i 's/transform eye rotate.*/transform eye rotate '$new_ch' 0 1 0/' $file

  #rendering the file
  echo 'rendering' $i ' from ' $cap
  ./source/scene_load_test

  #padding for ffmpeg
  convert test1.ppm 'frms/frame'`printf "%04d" $i`'.png'
  
  ((i++))
done

#generating the video
ffmpeg -r 30 -i frms/'frame%04d.png' anim/anim_$cap.mp4

#cleanup if needed
#rm -rf frms
#careful with stored videos
#rm anim