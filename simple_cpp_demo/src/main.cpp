#include <iostream>
#include "math_func.h"

int main()
{
    int x = 10;
    int y = 3;
    int res_add = add(x, y);
    int res_sub = sub(x, y);

    std::cout << "x + y = " << res_add << std::endl;
    std::cout << "x - y = " << res_sub << std::endl;

#ifdef PRINT_DEBUG
    std::cout << "【调试模式开启】" << std::endl;
#endif

    return 0;
}
