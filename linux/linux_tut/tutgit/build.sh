#! /bin/bash
mkdir build
cd build
rm -R cmake_files
rm a.out
mkdir cmake_files
cd cmake_files
cmake ../..
make -j8
cp a.out ../a.out;cp a.map ../a.map;cp a.lst ../a.lst;
cd ..
rm -R cmake_files
