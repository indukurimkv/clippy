#!/bin/bash

cdmk (){
  mkdir -p $1
  cd "$1"
}

workdir=$(pwd)

cdmk "$workdir/build"

cmake ..
make
