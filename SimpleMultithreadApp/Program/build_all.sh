#!/bin/bash

cd ./program_1;
mkdir build;
cd ./build;
cmake ..;
make;
mv program1 ../../;


cd ../../program_2;
mkdir build;
cd ./build;
cmake ..;
make;
mv  program2 ../../;




