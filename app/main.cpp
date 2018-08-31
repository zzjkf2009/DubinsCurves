/**
 * @Author: Zejiang Zeng
 * @Date:   2018-02-28T19:06:34-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: main.cpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T18:14:53-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */

 #include "Dubinscurves.h"
 #include "DrawDubinsCurve.h"
 #include "opencv2/opencv.hpp"
 #define PI 3.14159265

int main () {
        cv::Mat img(100,100,CV_8UC3,cv::Scalar(255,255,255));
        int Radius = 10;
        int r = 5;
        DrawDubinsCurve drawdubins(img,30.22,70.6,PI/4,70.0,30.0,PI/2,Radius,r);
        cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE);
        cv::imshow( "Display window",img);
        cv::waitKey(10000);
        return 0;
}
