#pragma once
#include<graphics.h>
//解决EasyX载入透明背景的PNG图片时，透明背景变成黑色背景的问题（CSDN上给出了两种解决方案，这个是方法一）
void drawAlpha(IMAGE* picture, int  picture_x, int picture_y); //x为载入图片的X坐标，y为Y坐标