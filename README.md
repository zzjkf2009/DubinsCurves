# Cartesian_space_Breadth First Search

## Overview
This is the Dubinscurves base class that will find the proper Dubins curve based on the initial and goal pose (location and direction). The proper path will be drawn with OpenCV by a derived class DrawDubins. It also can be further used for providing essential info for mobile robots

## Pipeline
* Initial and Goal Pose
* Calculate the two circles (CW,CCW) for each pose
* Calculate the feasible path for each pair of circles.
* find shortest path among the paths

## Prerequisites
* Ubuntu 16.04
* Cmake
* OpenCV

## Installation and Build

Run as fellow:
```
 git clone --recursive https://github.com/zzjkf2009/DubinsCurves
 cd DubinsCurves
```
The repository includes the OpenCV library already and not need to download again. If OpenCV library is not included somehow:
```
 git clone https://github.com/opencv/opencv.git
```
And if build folder is not created then
```
 mkdir build
```

## Running and Demo
Run:
```
cd build
cmake ..
make
./app/shepp-app
```

- Path PNG:
![](https://github.com/zzjkf2009/DubinsCurves/blob/master/result/R_10_r_5.png)




## Library
* OpenCV
OpenCV is an open source C++ library for image processing and computer vision, originally developed by Intel and now supported by Willow Garage.
It is a library of many inbuilt functions mainly aimed at real time image processing. Now it has several hundreds of image processing and computer vision algorithms which make developing advanced computer vision applications easy and efficient. More details see: https://docs.opencv.org/2.4/index.html
* Gtest
Google Test is a unit testing library for the C++ programming language, based on the xUnit architecture. More details cna be find at: https://github.com/google/googletest
* Gmock
Google Mock is an extension to Google Test for writing and using C++ mock classes. See the separate Google Mock documentation at https://github.com/google/googletest/blob/master/googlemock/README.md

Reference:
- http://home.deib.polimi.it/gini/robot/docs/Rob10bis.pdf
- http://www.xml-data.org/JSJYY/2017-7-2114.htm
