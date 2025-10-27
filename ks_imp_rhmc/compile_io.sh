#!/bin/bash

if [ -z "$PATH_TO_QIO" ]
then
  echo "Environment variable PATH_TO_QIO unset, exiting..."
  exit
fi

if [ -z "$PATH_TO_QMP" ]
then
  echo "Environment variable PATH_TO_QMP unset, exiting..."
  exit
fi

if [ ! -f "./Makefile" ]
then
  cp ../Makefile .
fi

if [ -f "./io" ]
then
  rm ./io
fi

OPT="-O3 -ffast-math" \
CTIME="-DNERSC_TIME -DCGTIME -DFFTIME -DGATIME -DGFTIME -DREMAP -DPRTIME -DIOTIME" \
MY_CC=mpicc \
MY_CXX=mpicxx \
PRECISION=2 \
MPP=true \
WANTQIO=true \
WANTQMP=true \
QIOPAR=${PATH_TO_QIO} \
QMPPAR=${PATH_TO_QMP} \
make -j 10 io
