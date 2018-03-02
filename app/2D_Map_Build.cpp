/**
 * @Author: Zejiang Zeng <zzj>
 * @Date:   2018-03-02T16:44:02-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: 2D_Map_Build.cpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T18:14:41-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 * @brief This is the main source file that build a 2D map based on the given
 * map, please check the map https://github.com/zzjkf2009/Bredth_First_Search/2D_Map.png
 */


#include "opencv2/opencv.hpp"
#include "grid_map_build.hpp"
#include "2D_Map_Build.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void Map_Build::ToOpenCVCord(vector<Point> &p) {
        for(auto &i : p) {
                i.y = 150 - i.y;
        }
}

void Map_Build::ToOpenCVCord(Point &p) {
        p.y = 150 - p.y;
}


cv::Mat Map_Build::Create_the_Map() {
        Mat img(150, 250, CV_8UC3);
        img.setTo(255);

        vector< Point> contour;
        Point ptss[6];
        ptss[0] = Point(120,55);
        ptss[1] = Point(158, 51);
        ptss[2] = Point(165, 89);
        ptss[3] = Point(188, 51);
        ptss[4] = Point(168, 14);
        ptss[5] = Point(145, 14);


        contour.push_back(ptss[1]);
        contour.push_back(ptss[2]);
        contour.push_back(ptss[3]);
        contour.push_back(ptss[4]);
        ToOpenCVCord(contour);


        Point p[4];
        p[0] = Point(120,95);
        p[1] = Point(158, 99);
        p[2] = Point(168, 136);
        p[3] = Point(145, 136);
        cv::fillConvexPoly(img, p, 4, cv::Scalar(250, 0, 0));

        cv::fillConvexPoly(img,            //Image to be drawn on
                           contour,   //C-Style array of points
                           Scalar(255,0,0), //Color , BGR form
                           CV_AA, // connectedness, 4 or 8
                           0); // Bits of radius to treat as fraction


        Point rectangle_lowerleft(55,82.5);
        Point rectangle_upperight(105,37.5);
        rectangle(img, Rect(rectangle_lowerleft, rectangle_upperight), Scalar(255, 0, 0),-10);
        Point center(180,30);
        circle(img, center, 15, Scalar(255, 0, 0), -1,8);
        //namedWindow( "Display window", WINDOW_AUTOSIZE); // Create a window for display.
        //resizeWindow("Display window",200,300);
        Mat largerImg;
        //resize(img,largerImg,cv::Size(), 2, 2);
        //imshow( "Display window", largerImg );             // Show our image inside it.
        imwrite("2D.png", img);
        return img;

}
