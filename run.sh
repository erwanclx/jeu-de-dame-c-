#!/bin/bash

g++ "$1" -o ./build/"$1".build
./build/"$1".build