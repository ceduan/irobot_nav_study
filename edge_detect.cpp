#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat src = cv::imread("test.jpg");
    if(src.empty())
    {
        std::cout << "图片读取失败！请把 test.jpg 放到 build 文件夹" << std::endl;
        return -1;
    }

    cv::Mat gray, blur, edge;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blur, cv::Size(5,5), 1.5);
    cv::Canny(blur, edge, 50, 150);

    cv::imwrite("gray.jpg", gray);
    cv::imwrite("blur.jpg", blur);
    cv::imwrite("edge.jpg", edge);

    std::cout << "边缘检测完成，输出 gray.jpg blur.jpg edge.jpg" << std::endl;
    return 0;
}
