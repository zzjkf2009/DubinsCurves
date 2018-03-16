/**
 * @Author: Zejiang Zeng
 * @Date:   2018-03-02T09:36:18-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: grid_map_build.cpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T18:06:24-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */



#include <vector>
#include <cmath>
#include <stdexcept>
#include <list>
#include "opencv2/opencv.hpp"
#include "grid_map_build.hpp"



void gridMap::build_grid_map(const double& x_resolution_, const double& y_resolution_,std::vector<bool> &gridmap) {
        for(double x = x_resolution_/2; x < 250; x+=x_resolution_) {
                for (double y = y_resolution_/2; y < 150; y+=y_resolution_) {
                        if (isInsideCircle(x,y) || isInsideRect(x,y) || isInsidePoly(x,y))
                                gridmap.push_back(false);
                        else
                                gridmap.push_back(true);
                }
        }
}

bool gridMap::isInsideCircle(double x,double y) {
        cv::Point tem(x,y);
        return cv::norm(center_ - tem) < 15;
}

bool gridMap::isInsideRect(double x, double y) {
        return (x > 55 && x < 105 && y > 67 && y < 114);
}

bool gridMap::isInsidePoly(double x, double y) {
        return ((y+1.64*x-251.8 > 0) && (y+0.1*x-67.6 < 0) && (5.43*x -y - 806.7 < 0)) || ((5.43*x -y - 806.7 > 0)&&(y +1.65*x-361.6 < 0) && (1.85*x -y -296.8 < 0) && y > 14);
}

void gridMap::isStartValid() {
        if (gridmap[start_node_num] && start_node_num < gridmap.size())
                return;
        else
                throw std::invalid_argument( "Start node is invalid" );
}
void gridMap::isGaolValid() {
        if (gridmap[goal_node_num] && goal_node_num < gridmap.size())
                return;
        else
                throw std::invalid_argument( "Goal node is invalid" );
}

bool gridMap::opensetfind(std::list<int> values, int x){
        //auto it = std::begin(list);
        for(auto it = values.begin(); it != values.end(); ++it) {
                if (*it == x)
                        return true;
        }
        return false;
}


bool gridMap::Bredth_First_Search() {
        if(gridmap.empty())
                throw std::invalid_argument( "Map is empty" );
        auto startNode = std::make_shared<Node>(start_node_num,num_y);
        openlist_.push(startNode);
        openset_.push_back(start_node_num);
        std::vector<std::pair<int,int> > nears = {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
        while(!openlist_.empty()) {
                std::shared_ptr<Node> FrontNode = openlist_.front();
                /**    if(FrontNode->node_num == goal_node_num) {
                            //std::cout<<"Find the goal"<<std::endl;
                            drawPathVideo(FrontNode);
                            return true;
                    } **/
                openlist_.pop();
                openset_.pop_front();
                closedset_.insert(FrontNode->node_num);
                //  for(int i = -1; i < 2; i++) {
                //          for(int j = -1; j < 2; j++) {
                for(auto & i : nears) {
                        int new_x = FrontNode->x + i.first;
                        int new_y = FrontNode->y + i.second;
                        int new_node_num = new_x*num_y+new_y;
                        if( new_x < 0 || new_x  > num_x || new_y <= 1 ||new_y > num_y || closedset_.find(new_node_num)!=closedset_.end() ||opensetfind(openset_,new_node_num) || !gridmap[new_node_num])
                                continue;
                        else {
                                auto NeighborNode = std::make_shared<Node>(new_node_num,num_y);
                                NeighborNode->father = FrontNode;
                                //std::cout<<"node "<< NeighborNode->x<<" "<< NeighborNode->y<<" 's father is"<< FrontNode->x <<" "<<FrontNode->y<<std::endl;
                                openlist_.push(NeighborNode);
                                openset_.push_back(new_node_num);
                                if(NeighborNode->node_num == goal_node_num) {
                                        //  std::cout<<"Find the goal"<<std::endl;
                                        drawPathVideo(NeighborNode);
                                        return true;
                                }

                        }
                }
        }
        std::cout << "Not find" << '\n';
        return false;
}

void gridMap::drawPathVideo(std::shared_ptr<Node> Node) {
        if (img.empty())
                return;
        cv::VideoWriter video("outcpp.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10,
                              cv::Size(250, 150));
        int NumSteps = 0;
        while(Node->father != nullptr) {
                try {
                        cv::Point p1 = cv::Point(Node->x * x_resolution_,(num_y - Node->y-1)*y_resolution_);
                        cv::Point p2 = cv::Point( (Node->x+1) * x_resolution_,(num_y - Node->y-2)*y_resolution_);
                        cv::rectangle(img, p1, p2, cv::Scalar(0, 0, 0), -1, 8);

                        Node = Node->father;
                        ++NumSteps;
                        // Write the frame into the file 'outcpp.avi'
                        video.write(img);
                }
                catch (const std::exception& e) {
                        std::cout << e.what();
                }

        }
        // When everything done, release the video capture and write object
        video.release();
        std::cout << "There are "<<NumSteps<< " steps to find the goal" << '\n';
}
