#! /bin/bash

#path to the sdf
org_file="../source/animation.sdf"

start=0
cap=540

cd ../build
make
clear

#setting up files and directories
i=0
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
  cam_ch=$(echo $i*\(1+1/3\) | bc -l)
  sed -i 's/transform cam rotate.*/transform cam rotate '$cam_ch' 0 1 0/' $file
  #cube rotation, also troughout
  cube_ch=$(echo \(2/3\)*$i | bc -l)
  sed -i 's/transform ct_bx_0 rotate \([0-9]*\).\([0-9]*\) 1 1 1/transform ct_bx_0 rotate '$cube_ch' 1 1 1/' $file
  sed -i 's/transform ct_bx_1 rotate \([0-9]*\).\([0-9]*\) 1 1 1/transform ct_bx_1 rotate '$cube_ch' 1 1 1/' $file
  sed -i 's/transform ct_bx_2 rotate \([0-9]*\).\([0-9]*\) 1 1 1/transform ct_bx_2 rotate '$cube_ch' 1 1 1/' $file
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
  #disco ball down
  if [ $i -gt 150 ] && [ $i -le 210 ]; then
    num=$((210 - $i))
    step=$(echo 5-\($num/40*$num/20\) | bc -l)
    for j in {0..8}
    do
      #I shouldn't do this that dirty, but right now I really can't be bothered
      sed -i 's/transform up_sp_'$j' .*/transform up_sp_'$j' translate 0 -'$step' 0/' $file
    done
  fi
  #and up
  if [ $i -gt 370 ] && [ $i -le 430 ]; then
    num=$((370 - $i))
    step=$(echo 5-\($num/40*$num/20\) | bc -l)
    for j in {0..8}
    do
      sed -i 's/transform up_sp_'$j' .*/transform up_sp_'$j' translate 0 -'$step' 0/' $file
    done
  fi
  #other objs in
  if [ $i -gt 150 ] && [ $i -le 210 ]; then
    num=$((210 - $i))
    step=$(echo $num*$num*$num*0.001 | bc -l)
    sed -i 's/transform out_bx_0 .*/transform out_bx_0 translate 0 0 -'$step'/' $file
    sed -i 's/transform out_bx_1 .*/transform out_bx_1 translate 0 0 '$step'/' $file
    sed -i 's/transform out_sp_0 .*/transform out_sp_0 translate 0 0 '$step'/' $file
    sed -i 's/transform out_sp_1 .*/transform out_sp_1 translate 0 0 '$step'/' $file
  fi
  #and out
  if [ $i -gt 330 ] && [ $i -le 390 ]; then
    num=$((330 - $i))
    step=$(echo $num*$num*$num*0.001 | bc -l)
    sed -i 's/transform out_bx_0 .*/transform out_bx_0 translate 0 0 -'$step'/' $file
    sed -i 's/transform out_bx_1 .*/transform out_bx_1 translate 0 0 -'$step'/' $file
    sed -i 's/transform out_sp_0 .*/transform out_sp_0 translate 0 0 -'$step'/' $file
    sed -i 's/transform out_sp_1 .*/transform out_sp_1 translate 0 0 -'$step'/' $file
  fi
  #moving the objects away to avoid artefacts
  if [ $i -gt 390 ]; then
    sed -i 's/transform out_bx_0 .*/transform out_bx_0 translate 0 1000 0/' $file
    sed -i 's/transform out_bx_1 .*/transform out_bx_1 translate 0 1000 0/' $file
    sed -i 's/transform out_sp_0 .*/transform out_sp_0 translate 0 1000 0/' $file
    sed -i 's/transform out_sp_1 .*/transform out_sp_1 translate 0 1000 0/' $file
  fi

  #rendering the file
  if [ $i -ge $start ]; then
    echo 'rendering' $i ' from ' $cap
    ./source/load_scene

    #padding for ffmpeg
    convert animation.ppm 'frms/frame'`printf "%04d" $i`'.png'
  fi
  ((i++))
done

#generating the video
ffmpeg -r 30 -i frms/'frame%04d.png' anim/anim_$cap.mp4

#cleanup if needed
#rm -rf frms
#careful with stored videos
#rm anim