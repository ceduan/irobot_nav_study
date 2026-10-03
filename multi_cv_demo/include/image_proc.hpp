#ifndef IMAGE_PROC_HPP
#define IMAGE_PROC_HPP

#include <opencv2/opencv.hpp>

// 声明一个灰度转换函数：告诉编译器，后面会实现这个函数
void to_gray(cv::Mat &src, cv::Mat &dst);

#endif
