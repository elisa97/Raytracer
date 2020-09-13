#! /bin/bash

#path to the sdf
org_file="../source/animation.sdf"

cap=540
i=0
ch=1.5

cd ../build
make
clear

#setting up files and directories

rm animation.tmp
cp $org_file .
mv animation.sdf animation.tmp
file="animation.tmp"

if [ ! -d "frms/" ]; then
  echo 'created folder frms'
  mkdir frms
fi

if [ ! -d "anim/" ]; then
  echo 'created folder anim'
  mkdir anim
fi

if [ $cap -lt $i ]; then
  tmp=$cap
  cap=$i
  i=$tmp
fi

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
  #the "staircase" in (60 to 150)
  if [ $i -ge 60 ] && [ $i -le 150 ]; then
    num=$(($i - 60))
    for j in {0..11}
    do
      step=$(echo -8+1/12*$num+$j*2/10 | bc -l)
      step_int=$(echo \($step-1\)/1 | bc)
      if [ $step_int -ge -1 ]; then
        step=-1
      fi
      sed -i 's/transform mid_bx_'$j' .*/transform mid_bx_'$j' translate 0 '$step' 0/' $file
      sed -i 's/transform mid_sp_'$j' .*/transform mid_sp_'$j' translate 0 '$step' 0/' $file
    done
  fi
  #the "staircase" out (390 to end)
  if [ $i -ge 390 ]; then
    num=$(($i - 390))
    for j in {0..11}
    do
      step=$(echo -3.4+1/11*$num+$j*2/10 | bc -l)
      step_int=$(echo \($step-1\)/1 | bc)
      if [ $step_int -lt -1 ]; then
        step=-1
      fi
      sed -i 's/transform mid_bx_'$j' .*/transform mid_bx_'$j' translate 0 '$step' 0/' $file
      sed -i 's/transform mid_sp_'$j' .*/transform mid_sp_'$j' translate 0 '$step' 0/' $file
    done
  fi
  #disco ball
  if [ $i -gt 150 ] && [ $i -le 210 ]; then
    num=$((210 - $i))
    step=$(echo 5-\($num/40*$num/20\) | bc -l)
    echo $step
    for j in {0..8}
    do
      #I shouldn't do this that dirty, but right now I really can't be bothered
      sed -i 's/transform up_sp_'$j' .*/transform up_sp_'$j' translate 0 -'$step' 0/' $file
    done
  fi

  if [ $i -gt 370 ] && [ $i -le 430 ]; then
    num=$((370 - $i))
    step=$(echo 5-\($num/40*$num/20\) | bc -l)
    echo $step
    for j in {0..8}
    do
      #I shouldn't do this that dirty, but right now I really can't be bothered
      sed -i 's/transform up_sp_'$j' .*/transform up_sp_'$j' translate 0 -'$step' 0/' $file
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