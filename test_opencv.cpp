#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
	//读取图片
	cv::Mat src = cv::imread("test.jpg");
	if(src.empty())
	{
		std::cout << "图片读取失败！确认test.jpg放在build文件夹下:" << std::endl;
		return -1;
	}
	cv::Mat gray;
	// BGR彩色图转灰度图，VSLAM/相机标定第一部预处理
	cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	//保存灰度图像
	cv::imwrite("gray_test.jpg",gray);
	std::cout << "灰度转换完成，已输出gray_test.jpg" << std::endl;
	return 0;
}
