
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstudy.h>

using namespace std;
using namespace cv;

#define WINDOW_NAME "win"

void onMouse(int event ,int x,int y,int flags,void* param);
void drawRect(Mat& img,Rect box);

Rect rect;
bool drawingbox=false;
RNG rng(12345);



int main()
{
    rect=Rect(-1,-1,0,0);
    Mat img,tmp;
    img=imread("cat.png");
    img.copyTo(tmp);

    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, onMouse,(void*)&img);
    while(1){
        img.copyTo(tmp);
        if(drawingbox)  drawRect(tmp,rect);
        imshow(WINDOW_NAME,tmp);
        if(waitKey(10)==27)  break;
    }

    return 0;
}

void onMouse(int event, int x, int y, int flags, void *param)
{

    Mat& img=*(Mat*) param;
    switch(event)
    {
        case EVENT_MOUSEMOVE:
            if(drawingbox){
                rect.width=x-rect.x;
                rect.height=y-rect.y;
            }
            break;
        case EVENT_LBUTTONDOWN:
            drawingbox=true;
            rect=Rect(x,y,0,0);
            break;
        case EVENT_LBUTTONUP:
            drawingbox=false;
            if(rect.width<0){
                rect.x+=rect.width;
                rect.width*=-1;
            }
            if(rect.height<0){
                rect.y+=rect.height;
                rect.height*=-1;
            }
            drawRect(img,rect);
            break;
    }
}


void drawRect(Mat &img, Rect box)
{
   rectangle(img,box.tl(),box.br(),Scalar(rng.uniform(0,255),
                                          rng.uniform(0,255),rng.uniform(0,255)));
}











