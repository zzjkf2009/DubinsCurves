/**
 * @Author: Zejiang Zeng
 * @Date:   2018-03-02T17:53:11-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Filename: 2D_Map_Build.hpp
 * @Last modified by:   Zejiang Zeng
 * @Last modified time: 2018-03-02T18:13:25-05:00
 * @Copyright: (C) 2017 Zejiang Zeng - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 */
 #include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
class Map_Build {
public:
cv::Mat Create_the_Map();
private:
void ToOpenCVCord(vector<Point> &p);
void ToOpenCVCord(Point &p);
};
