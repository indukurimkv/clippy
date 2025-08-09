#!/bin/bash

cdmk (){
  mkdir -p $1
  cd "$1"
}

workdir=$(pwd)
mkdir -p $workdir/lib

echo "Creating build directory for clip"
cdmk ./clip/build

clip_params=""
if (( "_$1" == "_release" )); then
  clip_params="$clip_params -DCMAKE_BUILD_TYPE=Release"
else
  clip_params="$clip_params -DCMAKE_BUILD_TYPE=Debug"
fi

echo "Buidling libclip"
cmake .. $clip_params
make
cp ./libclip.a $workdir/lib/

cdmk "$workdir/build"

cmake ..
make
