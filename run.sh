#!/bin/bash

rm ./build/"$1".build
g++ "$1" -o ./build/"$1".build
./build/"$1".build