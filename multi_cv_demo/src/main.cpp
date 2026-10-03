#include <opencv2/opencv.hpp>
#include "image_proc.hpp"

int main()
{
    // 读取图片
    cv::Mat src = cv::imread("../res/test.jpg");
    if(src.empty())
    {
        printf("图片读取失败，请检查图片是否放到build文件夹\n");
        return -1;
    }
    cv::Mat dst;
    // 调用刚才写好的灰度函数
    to_gray(src, dst);

    cv::imshow("原图", src);
    cv::imshow("灰度图", dst);
    cv::waitKey(0);
    return 0;
}
