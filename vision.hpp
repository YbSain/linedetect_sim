// vision.hpp
#ifndef VISION_HPP
#define VISION_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>
#include <signal.h>
#include "dxl.hpp"

// Namespace 및 외부 변수 선언
using namespace cv;
using namespace std;

extern bool ctrl_c_pressed;
extern Rect targetBoundingBox;
extern Point2d targetCenter;
extern bool isTarget;

// 함수 선언
void ctrlc(int);
Mat makethresh(Mat frame);
Mat Labeling(Mat displaymorph, Mat Grayframe);
int getError(Mat& thresh, Point& tmp_pt);

#endif // VISION_HPP
