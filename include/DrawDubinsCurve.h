/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-08-31T12:14:09-04:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: DrawDubinsCurve.h
 * @Last modified by:   yzy
 * @Last modified time: 2018-08-31T12:14:20-04:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */
#ifndef DRAWDUBINSCURVE_H
#define DRAWDUBINSCURVE_H

#include "opencv2/opencv.hpp"
#include "Dubinscurves.h"

/**
 * [DrawDubinsCurve this is a derived class of base class Dubinscurves, and and the main
 * purpose of this class was to using opencv to draw the dubins curves]
 */
class DrawDubinsCurve : public Dubinscurves {
public:
cv::Mat img;
//Constructor, call base Constructor
DrawDubinsCurve(cv::Mat img,double init_X,double init_Y,double init_theta, double goal_X,double goal_Y,double goal_theta,int R,int r) : Dubinscurves(init_X,init_Y,init_theta,goal_X,goal_Y,goal_theta,R,r), img(img) {
        DrawDubins(Dubinscurves::Dubins_init,Dubinscurves::Dubins_goal);
}
//Draw the circle using OpenCV
void DrawCicle(std::vector<double> center,cv::Mat img) const;
// Draw circles and tangent lines
void DrawDubins(std::vector<double> center_init, std::vector<double> center_goal);
};
#endif
