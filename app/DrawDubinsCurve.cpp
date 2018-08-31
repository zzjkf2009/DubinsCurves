/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-08-20T10:05:17-04:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: DrawDubinsCurve.cpp
 * @Last modified by:   yzy
 * @Last modified time: 2018-08-20T10:06:46-04:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 * @Descriptioin: This is a derived class from the base class Dubinscurves, and the main
 * purpose of this class was to using opencv to draw the dubins curves
 */
#include "opencv2/opencv.hpp"
#include "DrawDubinsCurve.h"



/**
 * [DrawDubinsCurve::DrawCicle draw circle]
 * @param center [cneter of the circle 1 by 4 vector [x,y,0/1,r]]
 * @param img    [img to draw]
 */
void DrawDubinsCurve::DrawCicle(std::vector<double> center,cv::Mat img) const {
        cv::Point center_point = cv::Point(floor(center[0]),floor(center[1]));
        std::cout << "The Radius is "<<center[3] << '\n';
        cv::circle(img, center_point, center[3],cv::Scalar(0,0,0),1,8);
}
/**
 * [DrawDubinsCurve::DrawDubins draw circles and tagent line ]
 * @param center_init [ center of the inital circle 1 by 4 vector]
 * @param center_goal [center of the final circle 1 by 4 vector]
 */
void DrawDubinsCurve::DrawDubins(std::vector<double> center_init, std::vector<double> center_goal) {
        DrawCicle(center_init,img);
        DrawCicle(center_goal,img);
        std::vector<double> tangentPoints = Dubinscurves::getTangents(center_init, center_goal);
        cv::Point point_A = cv::Point(floor(tangentPoints[0]),floor(tangentPoints[1]));
        cv::Point point_B = cv::Point(floor(tangentPoints[2]),floor(tangentPoints[3]));
        line(img,point_A,point_B,cv::Scalar(0,0,255),1,CV_AA);
}
