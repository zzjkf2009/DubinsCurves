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

 #include "opencv2/opencv.hpp"
 #include "grid_map_build.hpp"
 #include "2D_Map_Build.hpp"
 #include <iostream>
int main()
{
        Map_Build map;
        cv::Mat img = map.Create_the_Map();
        cv::Point start_1 = cv::Point(30,80);
        cv::Point goal_1 =  cv::Point(200,50);
        gridMap gridmap(1,1,start_1,goal_1);
        gridmap.img = img;
        if(gridmap.Bredth_First_Search())
                std::cout<<"Find the goal"<<std::endl;
        else
                std::cout<<"Goal not find"<<std::endl;
        namedWindow( "Display window", WINDOW_AUTOSIZE);
        imshow( "Display window", gridmap.img);
        imwrite("Path.png", gridmap.img);
        cv::waitKey(10000);
        return 0;
}
