#include <iostream>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ShowPic()
{
    Mat img;
    img = imread("PASA002.png");
    imshow("Original Image", img);
    waitKey();
}

void  CamShow()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;
    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
}

int main()
{

    //ShowPic();
    CamShow();

    return 0;


}



