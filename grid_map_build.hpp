#include <vector>
#include <cmath>
#include <tgmath.h>
#include <queue>
#include <set>
#include <memory>
#include "opencv2/opencv.hpp"


class gridMap {

public:
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
void build_grid_map(const double& x_resolution_, const double& y_resolution_,std::vector<bool>&gridmap);

bool isInsideCircle(double x,double y);

bool isInsideRect(double x, double y);

bool isInsidePoly(double x, double y);

bool Bredth_First_Search();

void isStartValid();
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
void drawPathVideo(std::shared_ptr<Node> Node);




};
