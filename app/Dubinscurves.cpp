/**
 * @Author: Zejiang Zeng <zzj>
 * @Date:   2018-08-08T13:01:26-04:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: Dubinscurves.cpp
 * @Last modified by:   zzj
 * @Last modified time: 2018-08-08T13:01:49-04:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 * @brief: This is the class that can generate the dubins curve by given the inital and
 * goal vector,with a minmal turning Radius R
 */
#include "Dubinscurves.h"
#include "DrawDubinsCurve.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <cmath>
#include <limits>
#define PI 3.14159265


/** the two circles (clockwise and counterclockwise) which are tangent to the
   velocity vector (initalV or goalV), so there will be two circles for each of vectors
   and the centers of the circles are C1 and C2
   see more info at: http://www.xml-data.org/JSJYY/2017-7-2114.htm
 **/

/**
 * [Dubinscurves::GenerateInitCirecle Find the centers of the circles for the inital velocity vector and Radius]
 * @param R [Radius]
 */
void Dubinscurves::GenerateInitCirecle(int R) {
// ->CP = +- (sin(theta), cos(theta))
// ->OC = ->OP - R* ->CP
        std::cout<<"the inital velocity direction is "<< initalV[2]<<std::endl;
        std::cout<<"the sin value is "<< sin(initalV[2]) <<std::endl;
        init_center_counterclockwise.push_back(initalV[0] - R* sin(initalV[2]));
        init_center_counterclockwise.push_back(initalV[1] - R* cos(initalV[2]));
        init_center_counterclockwise.push_back(0.0); // The third values will record the direction of the turning 0 means counterclockwise,
        // and 1 means clockwise
        init_center_counterclockwise.push_back(R);

        init_center_clockwise.push_back(initalV[0] + R* sin(initalV[2]));
        init_center_clockwise.push_back(initalV[1] + R* cos(initalV[2]));
        init_center_clockwise.push_back(1.0); // means clockwise
        init_center_clockwise.push_back(R);

}
/**
 * [Dubinscurves::GenerateoalGCirecle Find the center of the circle when knowing the velocity direction and Radius]
 * @param r [Radius]
 */
void Dubinscurves::GenerateoalGCirecle(int r) {
        goal_center_counterclockwise.push_back(goalV[0] - r* sin(goalV[2]));
        goal_center_counterclockwise.push_back(goalV[1] - r* cos(goalV[2]));
        goal_center_counterclockwise.push_back(0.0); // if it is ccw then is 0
        goal_center_counterclockwise.push_back(r);

        goal_center_clockwise.push_back(goalV[0] + r* sin(goalV[2]));
        goal_center_clockwise.push_back(goalV[1] + r* sin(goalV[2]));
        goal_center_clockwise.push_back(1.0); // if it is cw then lable as 1
        goal_center_clockwise.push_back(r);
}


/**
 * [Dubinscurves::getTangents This is the function that will generate a feasiable line for two dubins circles]
 * @param center1 [inital circle with Radius R]
 * @param center2 [goal circle with Radius r]
 */
std::vector<double> Dubinscurves::getTangents(std::vector<double> center1, std::vector<double> center2) {
//Calculate the distance between two Centers
        double Dis = sqrt((center1[0] - center2[0])*(center1[0] - center2[0]) + (center1[1] - center2[1])*(center1[1] - center2[1]));
        double vx = (center1[0] - center2[0])/Dis;
        double vy = (center1[1] - center2[1])/Dis;
        // Let A,B be the centers and C,D be points at which the tangent touches first and second circles, and n be the normal vector to it
        // we have the system :
        // n*n = 1 (n is unit vector)
        // C = A + r1*n
        // D = B +/- r2*n
        // n * CD = 0
        // n * CD = n *(AB +/- r2*n - r1*n) = AB*n -(r1 +/- r2) = 0
        // AB * n = (r1 +/- r2)
        // v*n = (r1 +/- r2)/d where v is the unit vector of AB
        // mroe details can be find at: https://gieseanw.wordpress.com/2012/10/12/a-comprehensive-setp-by-setp-tutorial-to-computing-dubins-paths/
// If sign1 is 1 then the tangent line will be outter tangent, if sign1 is -1, then it will be innner tangent
        std::vector<double> points; // which will be 4 * 2 pairs (x,y) of points, so 16 values in total
        for(int sign1 = 1; sign1 >= -1; sign1-= 2) {
                double c = (R - sign1*r)/Dis;
                if(c*c > 1.0) continue;
                double h = sqrt(std::max(0.0, 1.0 - c*c));
                for(int sign2 = 1; sign2 >= -1; sign2 -= 2) {
                        double nx = vx*c - sign2*h*vy;
                        double ny = vy*c + sign2*h*vx;
                        points.push_back(center1[0] + R*nx);
                        points.push_back(center1[1] + R*ny);
                        points.push_back(center2[0]+ sign1*r*nx);
                        points.push_back(center2[1]+ sign1*r*ny);
                }

        }

// Lable the turning direction using the cross product of the intial veclocity direction and the center to the start position
// V_init * OP (cross product) where OP is (P_x - O_x, P_y - O_y)
//  (initalV[0] - center1[0],initalV[1] - center[1])
//  Calculate the cross product
        double init_corss = cos(initalV[2])*(initalV[1] - center1[1]) - sin(initalV[2])*(initalV[0] - center1[0]);

// Only one of the four lines will be the feasiable line to make it right
// if the turning direction of the two circles are the same (both clockwise), then the line will be outter tangent, otherwise, it will be
// innner tangent line
        double outter_1, outter_2, inner_1, inner_2;
        if(abs(center1[2] -center2[2]) < 0.01) {
                // if the turning direction is same, then only first two (outter tangent lines are needed to be check)
                // determine the direction (ccw,cw) by checking the cross product of OA and AB (A is the intersection between the line and the inital circle and B is point on goal circle)
                outter_1 = (points[2]- points[0])*(points[1] - center1[1]) - (points[3]-points[1])*(points[0] - center1[0]);
                outter_2 = (points[6]- points[4])*(points[5] - center1[1]) - (points[7]-points[5])*(points[4] - center1[0]);
                int result = determinePoints(init_corss,outter_1,outter_2);
                if(result == 1) {
                        std::vector<double> v = {points[0],points[1],points[2],points[3]};
                        return v;
                }
                else if(result == 2) {
                        std::vector<double> v = {points[4],points[5],points[6],points[7]};
                        return v;
                }
                else
                        std::cout<<"Check the outter code"<<std::endl;

        }
        else if(abs(center1[2] -center2[2]) > 0.99 && abs(center1[2] -center2[2]) < 1.01) {
                // if the turning direction is oppsite, then only last two (inner tangent lines) are needed to be check
                // also determine the direction by checking the cross product
                inner_1 = (points[10]- points[8])*(points[9] - center1[1]) - (points[11]-points[9])*(points[8] - center1[0]);
                inner_2 = (points[14]- points[12])*(points[13] - center1[1]) - (points[15]-points[13])*(points[4] - center1[0]);
                int result = determinePoints(init_corss,inner_1,inner_2);
                if(result == 1) {
                        std::vector<double> v = {points[8],points[9],points[10],points[11]};
                        return v;
                }
                else if(result == 2) {
                        std::vector<double> v = {points[12],points[13],points[14],points[15]};
                        return v;
                }
                else
                        std::cout<<"Check the inner code"<<std::endl;
        }
        else {
                std::cout<<"The direction of the circle is neither same nore oppsite"<<std::endl;
        }

}
/**
 * [Dubinscurves::determinePoints To determine which points of the two possible tagnet lines by finding the direction (cross product)]
 * @param  init_corss [direction (cross product of the init veclocity and Radius)]
 * @param  a          [cross product of one line]
 * @param  b          [cross product of the other line]
 * @return            [line number]
 */
int Dubinscurves::determinePoints(double init_corss,double a, double b) {
        if (a * b > 0) {
                std::cout<< "the two tangent lines should not be in same direction"<<std::endl;
                return 0;
        }
        else if (a * init_corss > 0 && b * init_corss < 0)
                return 2;
        else if (b * init_corss > 0 && a * init_corss < 0)
                return 1;
        else {
                std::cout<< "Something strange here"<<std::endl;
                return 0;
        }

}

/**
 * [Dubinscurves::findMinLine For all possible circle paris,find the one has the smallest distance]
 */
void Dubinscurves::findMinLine() {
        double dis_IcGc = calculateDis(init_center_clockwise,goal_center_clockwise);
        double dis_IcGcc = calculateDis(init_center_clockwise,goal_center_counterclockwise);
        double dis_IccDc = calculateDis(init_center_counterclockwise,goal_center_clockwise);
        double dis_IccGcc = calculateDis(init_center_counterclockwise,goal_center_counterclockwise);
        std::vector<double> fourlines = {dis_IcGc,dis_IcGcc,dis_IccDc,dis_IccGcc};
        //std::cout << "The dis_IcGc is " <<dis_IcGc<< '\n';
        double tem = DBL_MAX; int index = -1;
        for(int i = 0; i< 4; i++) {
                if(fourlines[i] < tem) {
                        tem = fourlines[i];
                        index = i;
                }
        }
        switch (index) {
        case -1:
                std::cout << "Some thing wrong with the index" << '\n';
                break;
        case 0:
                //DrawDubins(init_center_clockwise,goal_center_clockwise);
                Dubins_init = init_center_clockwise;
                Dubins_goal = goal_center_clockwise;
                std::cout << "init_center_clockwise and goal_center_clockwise" << '\n';
                break;
        case 1:
                //  DrawDubins(init_center_clockwise,goal_center_counterclockwise);
                Dubins_init = init_center_clockwise;
                Dubins_goal = goal_center_counterclockwise;
                std::cout << "init_center_clockwise and goal_center_counterclockwise " << '\n';
                break;
        case 2:
                // DrawDubins(init_center_counterclockwise,goal_center_clockwise);
                Dubins_init = init_center_counterclockwise;
                Dubins_goal = goal_center_clockwise;
                std::cout << "init_center_counterclockwise and goal_center_clockwise" << '\n';
                break;
        case 3:
                //  DrawDubins(init_center_counterclockwise,goal_center_counterclockwise);
                Dubins_init = init_center_counterclockwise;
                Dubins_goal = goal_center_counterclockwise;
                std::cout << "init_center_counterclockwise and goal_center_counterclockwise" << '\n';
                break;
        }

}

/**
 * [Dubinscurves::calculateDis description]
 * @param centerInit [description]
 * @param centerGoal [description]
 * @param tangentPoints [4 by 1 vector that contains the tagent points A and B on both circles]
 */
double Dubinscurves::calculateDis(std::vector<double> centerInit, std::vector<double> centerGoal){
        std::vector<double> tangentPoints = getTangents(centerInit,centerGoal);
        // For intial circle
        // calculate the angle by using dot product cos(theta) =  (ax * bx  + ay * by)/(sqrt(ax*ax+ay*ay) + sqrt(bx*bx + by* by))
        // where OA dot OP for inital circle, OP is (initalV[0] - centerInit[0], initalV[1] - centerInit[1])
        // where OA is (tangentPoints[0] - centerInit[0], tangentPoints[1] - centerInit[1])
        double ax = initalV[0] - centerInit[0]; double bx = tangentPoints[0] - centerInit[0];
        double ay = initalV[1] - centerInit[1]; double by = tangentPoints[1] - centerInit[1];
        double theta_init = acos((ax * bx  + ay * by)/(sqrt(ax*ax+ay*ay) * sqrt(bx*bx + by* by)));
        // using cross product of AB and  InitV to determine the direction for tagentline(cw, ccw)
        // AB: [tangentPoints[2]- tangentPoints[0], tangentPoints[3]-tangentPoints[1]]
        double sign_init = cos(initalV[2])*(tangentPoints[3]-tangentPoints[1]) - sin(initalV[2])*(tangentPoints[2]- tangentPoints[0]);
        if (sign_init < 0) {
                theta_init = PI -theta_init;
        }
        double Dis_Init =  theta_init * R;
        // For goal circle
        // Calculate the angle by using dot product cos(theta) =  (ax * bx  + ay * by)/(sqrt(ax*ax+ay*ay) + sqrt(bx*bx + by* by))
        // where OB dot OP for inital circle, OP is (goalV[0] - centerGoal[0], goalV[1] - centerGoal[1])
        // where OB is (tangentPoints[2] - centerGoal[0], tangentPoints[3] - centerGoal[1])
        ax  = goalV[0] - centerGoal[0]; bx = tangentPoints[2] - centerGoal[0];
        ay = goalV[1] - centerGoal[1];  by = tangentPoints[3] - centerGoal[1];
        double theta_goal = acos((ax * bx  + ay * by)/(sqrt(ax*ax+ay*ay) * sqrt(bx*bx + by* by)));
        // using cross product of AB and  goalV to determine the direction for tagentline(cw, ccw)
        // AB: [tangentPoints[2]- tangentPoints[0], tangentPoints[3]-tangentPoints[1]]
        double sign_igoal = cos(goalV[2])*(tangentPoints[3]-tangentPoints[1]) - sin(goalV[2])*(tangentPoints[2]- tangentPoints[0]);
        if (sign_igoal < 0) {
                theta_goal = PI -theta_goal;
        }
        double Dis_goal =  theta_goal * r;

        double AB = sqrt((tangentPoints[2]- tangentPoints[0])*(tangentPoints[2]- tangentPoints[0]) + (tangentPoints[3]-tangentPoints[1])*(tangentPoints[3]-tangentPoints[1]));
        return Dis_Init + AB + Dis_goal;

}

/*************************************************************************************************************************/
