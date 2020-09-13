#! /bin/bash

#path to the sdf
file="../source/animation.sdf"

cap=150
i=0
ch=1.5

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
#remove blank lines in the sdf
sed '/\n/d' $file

#important part
while [ $i -le $cap ]
do
  #rewriting lines in the file
  #cam rotation, happens troughout the animation
  cam_ch=$(echo $i*1.5 | bc -l)
  sed -i 's/transform cam rotate.*/transform cam rotate '$cam_ch' 0 1 0/' $file
  #cube rotation, also troughout
  cube_ch=$(echo $i*0.75 | bc -l)
  sed -i 's/transform ct_bx_0 rotate \([0-9]*\).\([0-9]*\) 1 1 0/transform ct_bx_0 rotate '$cube_ch' 1 1 0/' $file
  sed -i 's/transform ct_bx_1 rotate \([0-9]*\).\([0-9]*\) 1 1 0/transform ct_bx_1 rotate '$cube_ch' 1 1 0/' $file
  sed -i 's/transform ct_bx_2 rotate \([0-9]*\).\([0-9]*\) 1 1 0/transform ct_bx_2 rotate '$cube_ch' 1 1 0/' $file
  #scaling of the cube at the beginning (first 60 fames) and end (last 60 frames)
  if [ $i -le 59 ] || [ $i -ge 480 ]; then
    fac=$(($i % 60))
    if [ $i -le 59 ]; then
      cube_sc=$(echo 0.5+\($fac/60\)/2 | bc -l)
    else
      cube_sc=$(echo 0.5+\(1-\($fac/60\)\)/2 | bc -l)
    fi
    sed -i 's/transform ct_bx_0 scale.*/transform ct_bx_0 scale '$cube_sc' '$cube_sc' '$cube_sc'/' $file
    sed -i 's/transform ct_bx_1 scale.*/transform ct_bx_1 scale '$cube_sc' '$cube_sc' '$cube_sc'/' $file
    sed -i 's/transform ct_bx_2 scale.*/transform ct_bx_2 scale '$cube_sc' '$cube_sc' '$cube_sc'/' $file
  fi
  #the "staircase" 
  if [ $i -ge 60 ] && [ $i -le 150 ]; then
    num=$(($i - 60))
    for j in {0..11}
    do
      step=$(echo -8+1/12*$num+$j*2/10 | bc -l)
      step_int=${step%.*}
      if [ $step_int -ge -1 ]; then
        step=-1
      fi
      sed -i 's/transform mid_bx_'$j' .*/transform mid_bx_'$j' translate 0 '$step' 0/' $file
      sed -i 's/transform mid_sp_'$j' .*/transform mid_sp_'$j' translate 0 '$step' 0/' $file
    done
  fi
  #rendering the file
  echo 'rendering' $i ' from ' $cap
  ./source/load_scene

  #padding for ffmpeg
  convert animation.ppm 'frms/frame'`printf "%04d" $i`'.png'
  
  ((i++))
done

#generating the video
ffmpeg -r 30 -i frms/'frame%04d.png' anim/anim_$cap.mp4

#cleanup if needed
#rm -rf frms
#careful with stored videos
#rm anim