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
    // 调用灰度函数
    to_gray(src, dst);

    cv::imshow("原图", src);
    cv::imshow("灰度图", dst);

    // ==========新增：条件编译，控制图片保存==========
#ifdef SAVE_OUTPUT_IMAGE
    cv::imwrite("../res/gray_out.jpg", dst);
#endif

    cv::waitKey(0);
    return 0;
}
