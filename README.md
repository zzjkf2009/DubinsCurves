# Cartesian_space_Breadth First Search

## Overview

This is an exercise project to design a path planning components using high-quality software engineering practices. This project used Breadth First Search graph search algorithm to find an feasible path from start node to goal node. the Cartesian map is given. After define the start and goal node, it will generate a path. Opencv library was used to draw the map and the path to provide a intuitive graph for user.

## Pipeline
- The workspace is defined as a 250-by-150 map and there are three obstacles, one rectangle, one circle, one polynomial. Those three obstacles are represent by Half-plane and semi-algebraic  models.
- To simplify the problem, the grid map is reduced dimension from 2D to 1D vector of boolean, the number of total nodes is determined by the user defined resolution (x_resolution,y_resolution).  If the node is occupied (inside the obstacles), then it is marked as false, otherwise, it is true. I use the center of the node as a reference to calculate if the center is inside those Half-plane or semi-algebraic represented obstacle models.
- After the grid map is created, a Breadth First Search is applied to find the path from start node to goal node.
- The Cartesian map and path are drawn by OpenCV, and a video is create to demonstrate the path **IN REVERSE ORDER**, namely drawn from *goal node* back to *start node* !! And a .gif will be
attached result section. (start and goal node will be checked to see if they are valid)
- Original Map:
![](https://github.com/zzjkf2009/Breadth_First_Search/blob/master/result/2D_Map.png)

## Note
- The result of the search may vary depend on which neighbor among 8 neighbors is got searched first, my current first search node is the lower-left. {-1, 0, 1}
- Both of the following parameters can be defined from the *main.cpp*
(1) start and goal positions (2) x and y grid resolution
- In the gridMap class, function *build_grid_map* generate the "NodesSet" and "NodesInfoSet.
 function *Breadth_First_Search* implement Breadth First Search algorithm. Function *drawPathVideo* generate the graphical interface.

## Prerequisites
* Ubuntu 16.04
* Cmake
* OpenCV

## Installation and Build

Run as fellow:
```
 git clone --recursive https://github.com/zzjkf2009/Breadth_First_Search
 cd Breadth_First_Search
```
If OpenCV library is not cloned with the other file:
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

## Result
If there is a path, the path image and video will be generate in the *build* directory, meanwhile the path will be printed on the screen. If the start or goal node is invalid, the exception message will be noticed.

- Path PNG:
![](https://github.com/zzjkf2009/Breadth_First_Search/blob/master/result/Path.png)
- Path GIF:
![](https://github.com/zzjkf2009/Breadth_First_Search/blob/master/result/Path.gif)



## Test
After the build process, run the unit test program, you will see the result of all tests
run:
```
./build/test/cpp-test
```

## Library
* OpenCV
OpenCV is an open source C++ library for image processing and computer vision, originally developed by Intel and now supported by Willow Garage.
It is a library of many inbuilt functions mainly aimed at real time image processing. Now it has several hundreds of image processing and computer vision algorithms which make developing advanced computer vision applications easy and efficient. More details see: https://docs.opencv.org/2.4/index.html
* Gtest
Google Test is a unit testing library for the C++ programming language, based on the xUnit architecture. More details cna be find at: https://github.com/google/googletest
* Gmock
Google Mock is an extension to Google Test for writing and using C++ mock classes. See the separate Google Mock documentation at https://github.com/google/googletest/blob/master/googlemock/README.md
