/**
 * @Author: Zejiang Zeng
 * @Date:   2018-03-02T00:50:52-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: grid_map_build.hpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T17:47:42-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */



#include <vector>
#include <cmath>
#include <tgmath.h>
#include <queue>
#include <set>
#include <memory>
#include "opencv2/opencv.hpp"


class gridMap {

public:
/**
 * [constructor that assign the basic variables and check if start or gaol node is valid]
 * @param x_resolution [double]
 * @param y_resolution [double]
 * @param start        [cv::Point]
 * @param goal         [cv::Point]
 */
gridMap(double x_resolution, double y_resolution,cv::Point start,cv::Point goal) : x_resolution_(x_resolution),y_resolution_(y_resolution){
        build_grid_map(x_resolution_,y_resolution_,gridmap);
        num_x = std::ceil(250/x_resolution_);
        num_y = std::ceil(150/y_resolution_);
        start_node_num = start.x/x_resolution_*num_y + start.y/y_resolution_;
        goal_node_num = goal.x/x_resolution_*num_y + goal.y/y_resolution_;
        isStartValid();
        isGaolValid();
}
std::vector<bool> gridmap;
/**
 * [Create a cartisen map based on the resolution of x and y]
 * @param x_resolution_ [double]
 * @param y_resolution_ [double]
 * @param gridmap       [vector<bool>]
 */
void build_grid_map(const double& x_resolution_, const double& y_resolution_,std::vector<bool>&gridmap);
/**
 * [check if the point is inside the circle, circle cneter and radius are pre-defined]
 * @param  x [double]
 * @param  y [double]
 * @return   [bool]
 */
bool isInsideCircle(double x,double y);
/**
 * [check if the point is inside the rectangle]
 * @param  x [double]
 * @param  y [double]
 * @return   [bool]
 */
bool isInsideRect(double x, double y);
/**
 * [Check if the point is inside a polynomial geometry]
 * @param  x [double]
 * @param  y [double]
 * @return   [bool]
 */
bool isInsidePoly(double x, double y);
/**
 * [Apply Cartisen_space_Breadth algorith]
 * @return [bool]
 */
bool Bredth_First_Search();
/**
 * [Check if the start node is valid]
 */
void isStartValid();
/**
 * [Check if the goal node is valid ]
 */
void isGaolValid();
unsigned int num_x;
unsigned int num_y;
unsigned int start_node_num;
unsigned int goal_node_num;
cv::Mat img;
struct Node {
        Node(unsigned int ii,unsigned int num_y) :
                node_num(ii){
                father = NULL;
                x = ii/num_y;
                y = ii%num_y;
        }
        unsigned int node_num;
        unsigned int x;
        unsigned int y;
        std::shared_ptr<Node> father;
};

private:
double x_resolution_;
double y_resolution_;
cv::Point center_ = cv::Point(180,120);
std::queue<std::shared_ptr<Node> > openlist_;
std::set<int> openset_;
std::set<int> closedset_;
/**
 * [Draw the path from goal node back to start node]
 * @param Node [std::shared_ptr<Node>]
 */
void drawPathVideo(std::shared_ptr<Node> Node);




};
