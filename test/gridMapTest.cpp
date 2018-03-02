/**
 * @Author: Zejiang Zeng
 * @Date:   2018-03-01T23:32:19-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: gridMapTest.cpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T16:59:33-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */



#include <gtest/gtest.h>
#include <memory>
#include <stack>
#include <opencv2/opencv.hpp>
#include "grid_map_build.hpp"

struct gridMapTest : public ::testing::Test {
        cv::Point start_1 = cv::Point(50,60);
        cv::Point goal_1 =  cv::Point(80,60);
        std::shared_ptr<gridMap> gridmap = std::make_shared<gridMap>(1.0,1.0,start_1,goal_1);

};
/**
   *@brief test if the start or goal is invalid, error should be throwed
 */
TEST_F(gridMapTest,invalid_argumentTest) {
        cv::Point start_2 = cv::Point(450,60);
        cv::Point goal_2 =  cv::Point(880,60);
        EXPECT_ANY_THROW(std::shared_ptr<gridMap> gridmap = std::make_shared<gridMap>(1.0,1.0,start_2,goal_2));

}
/**
   *@brief test if basic variable are assigned correctly
 */
TEST_F(gridMapTest,basicVaribleTest){
        EXPECT_EQ(150,gridmap->num_y);
        EXPECT_EQ(250,gridmap->num_x);
        EXPECT_EQ(50*150+60,gridmap->start_node_num);
        EXPECT_EQ(80*150+60,gridmap->goal_node_num);
}
/**
   *@brief test if a point is inside th circle
 */
TEST_F(gridMapTest, isInsideCircleTest) {

        EXPECT_FALSE(gridmap->isInsideCircle(0.0,0.0));
        EXPECT_FALSE(gridmap->isInsideCircle(250.0,150.0));
        EXPECT_TRUE(gridmap->isInsideCircle(185.0,125.0));
}
/**
   *@brief test if a point is inside th rectangle
 */
TEST_F(gridMapTest,isInsideRectTest) {
        EXPECT_FALSE(gridmap->isInsideRect(0.0,0.0));
        EXPECT_FALSE(gridmap->isInsideRect(250.0,150.0));
        EXPECT_TRUE(gridmap->isInsideRect(60.0,90.0));
}
/**
   *@brief test if a point is inside th circle polynomial
 */
TEST_F(gridMapTest,isInsidePolyTest) {
        EXPECT_FALSE(gridmap->isInsidePoly(0.0,0.0));
        EXPECT_FALSE(gridmap->isInsidePoly(250.0,150.0));
        EXPECT_FALSE(gridmap->isInsidePoly(158.0,55.0));
        EXPECT_FALSE(gridmap->isInsidePoly(180.0,80.0));
        EXPECT_TRUE(gridmap->isInsidePoly(150.0,20.0));
        EXPECT_TRUE(gridmap->isInsidePoly(165.0,30.0));
        EXPECT_TRUE(gridmap->isInsidePoly(125.0,50.0));
        EXPECT_TRUE(gridmap->isInsidePoly(170.0,60.0));
}
/**
   *@brief test the grid map is built correctly
 */
TEST_F(gridMapTest,build_grid_mapTest) {
        EXPECT_EQ(150*250,gridmap->gridmap.size());
        EXPECT_TRUE(gridmap->gridmap[0]);
        EXPECT_TRUE(gridmap->gridmap[37400]);
        EXPECT_TRUE(gridmap->gridmap[70*150+50]);
        EXPECT_FALSE(gridmap->gridmap[185*150+125]);
        EXPECT_FALSE(gridmap->gridmap[60*150+90]);
        EXPECT_FALSE(gridmap->gridmap[165*150+30]);
}
/**
   *@brief test the search algorithm
 */
TEST_F(gridMapTest, SearchTest) {
        EXPECT_TRUE(gridmap->Bredth_First_Search());
}
