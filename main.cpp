 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <ctime>

 using namespace std;
 using namespace cv;

 /** 函数声明 */
 void detectAndDisplay( Mat frame );

 /** 全局变量 */
 string car_cascade_name = "cascade.xml";
 CascadeClassifier car_cascade;

//测试图片文件所在目录
 string  fun_dir="/home/echo/Downloads/opencv_traincascade/CarData/TestImages/test-";
 string dir;
 string win = "detect";

int main(int argc, const char ** argv)
{
    clock_t start_time, end_time;   //计算一个执行周期时间
    namedWindow(win);                 //创建窗口
//    char counts = '10';
//    dir = fun_dir + counts + ".pgm";
//    Mat img = imread(dir, CV_LOAD_IMAGE_COLOR);   //测试图片检测
    if( !car_cascade.load( car_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };      //加载级联分类器

    VideoCapture cap(0);    //读取视频
    if(!cap.isOpened())  {  return -1;  }
    Mat frame;
    Mat edges;

    bool stop = false;
    while(!stop)
    {
        start_time = clock();

        cap>>frame;                         //读取视频帧到frame
        imshow("frame", frame);
        detectAndDisplay(frame);   //使用级联分类器检测并显示

        if(waitKey(30) >=0)
            stop = true;

        end_time = clock();             //计算输出执行玩一次所用时间
        cout << (double)(end_time - start_time)  / CLOCKS_PER_SEC * 1000 << "ms" <<endl;
    }


//    detectAndDisplay(img);
//    waitKey(0);


    cvDestroyAllWindows();
}

 void detectAndDisplay( Mat frame )
 {
      std::vector<Rect> cars;
      Mat frame_gray;

      //图像预处理
      cvtColor( frame, frame_gray, CV_BGR2GRAY );
      equalizeHist( frame_gray, frame_gray );

//    imshow("gray", frame_gray);

      //--  多尺寸检测所有车辆
      car_cascade.detectMultiScale( frame_gray, cars, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      //标示出车辆位置
      for( int i = 0; i < cars.size(); i++ )
      {
        Point center( cars[i].x + cars[i].width*0.5, cars[i].y + cars[i].height*0.5 );
        ellipse( frame, center, Size( cars[i].width*0.5, cars[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }

    imshow(win, frame);     //显示出含有车辆标示的图片
}



