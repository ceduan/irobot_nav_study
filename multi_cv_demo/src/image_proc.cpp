#include "image_proc.hpp"

// 灰度函数的具体实现，写在这里
void to_gray(cv::Mat &src, cv::Mat &dst)
{
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
}
