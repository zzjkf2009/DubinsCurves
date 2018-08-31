/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-08-31T12:05:14-04:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: Dubinscurves.h
 * @Last modified by:   yzy
 * @Last modified time: 2018-08-31T12:11:23-04:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 * @brif this is the header file for the Dubinscurves class
 */
 #ifndef DUBINSCURVES_H
 #define DUBINSCURVES_H

#include <vector>

class Dubinscurves {
private:
// Min turning curvature Radius, here I assume the turning Radius is constant, we can also
// set two sets of Radius R and r
int R;  // init circle
int r; // goal circle
// Using (x, y, theta) to express the inital and goal position/directions
std::vector <double> initalV;
std::vector <double> goalV;

//Centers for init velocity vector
std::vector<double> init_center_clockwise;
std::vector<double> init_center_counterclockwise;

//Centers for goal velocity vector
std::vector<double> goal_center_clockwise;
std::vector<double> goal_center_counterclockwise;
//Generate the two circles for the inital vector with turning Radius R
void GenerateInitCirecle(int R);
//Generate the two circles for the goal vector with turning Radius R
void GenerateoalGCirecle(int r);
protected:
std::vector<double> Dubins_init;
std::vector<double> Dubins_goal;
public:
//Constructor
Dubinscurves() : initalV(3,0.0),goalV(3,0.0),R(0),r(0){
        GenerateInitCirecle(R);
        GenerateoalGCirecle(r);
}
// which R is the Radius of the inital circle and r is the Radius of the goal circles
Dubinscurves(double init_X,double init_Y,double init_theta, double goal_X,double goal_Y,double goal_theta,int R,int r) : R(R),r(r){
        initalV = {init_X,init_Y,init_theta};
        goalV = {goal_X,goal_Y,goal_theta};
        GenerateInitCirecle(R);
        GenerateoalGCirecle(r);
        findMinLine();
}


//find the four tangent lines for two circles
std::vector<double> getTangents(std::vector<double> center1, std::vector<double> center2);
int determinePoints(double init_corss,double a, double b);
void findMinLine();
double calculateDis(std::vector<double> centerInit, std::vector<double> centerGoal );

};

#endif
