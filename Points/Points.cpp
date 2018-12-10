# include <stdio.h>
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat DrawCrossC1(Mat gray, int i, int j){
	gray.at<unsigned char>(i,j)=255;
	gray.at<unsigned char>(i+1,j)=255;
	gray.at<unsigned char>(i-1,j)=255;
	gray.at<unsigned char>(i,j+1)=255;
	gray.at<unsigned char>(i,j-1)=255;
	return gray;
}

Mat DrawPoints(Mat img2){
	int barix = 0, bariy = 0,x,y;
	Point P;
	for(int i =0; i < 4; i++){
		P = Point(x,y);
		cin >> P.x >> P.y;
		barix+= P.x;
		bariy+= P.y;
		circle(img2,P,1,CV_RGB(0,0,255),2);
	}
	P.x = barix/4;
	P.y = bariy/4;
	circle(img2,P,1,CV_RGB(0,0,255),2);
	return img2;
}

Mat DrawCrossC3(Mat img3, int i, int j){
	Vec3b intensity;
	intensity.val[0] = 0;
	intensity.val[1] = 0;
	intensity.val[2] = 255;
	img3.at<Vec3b>(i,j)=intensity;
	img3.at<Vec3b>(i+1,j)=intensity;
	img3.at<Vec3b>(i-1,j)=intensity;
	img3.at<Vec3b>(i,j+1)=intensity;
	img3.at<Vec3b>(i,j-1)=intensity;
	return img3;
}

Mat DrawPolygone(Mat img4){
	int x, y;
	Point P1, P2, P3, P4;
	
	P1 = Point(x,y);
	cin >> P1.x >> P1.y;
	P2 = Point(x,y);
	cin >> P2.x >> P2.y;
	P3 = Point(x,y);
	cin >> P3.x >> P3.y;
	P4 = Point(x,y);
	cin >> P4.x >> P4.y;
	
	line(img4, P1, P2, Scalar(0,0,0), 2, LINE_8);
	line(img4, P2, P3, Scalar(0,0,0), 2, LINE_8);
	line(img4, P3, P4, Scalar(0,0,0), 2, LINE_8);
	line(img4, P4, P1, Scalar(0,0,0), 2, LINE_8);
	
	return img4;
}

int main( int argc, char** argv ){
	Mat img;
	img = cv:: imread("lena.jpg");
	
	Mat gray;
	cvtColor(img, gray, cv::COLOR_RGB2GRAY);
	
	Mat gray2 = DrawCrossC1(gray,100,100);
	
	Mat img2;
	img2 = cv:: imread("lena.jpg");
	img2 = DrawPoints(img2);
	
	Mat img3;
	img3 = cv:: imread("lena.jpg");
	img3 = DrawCrossC3(img3,200,300);
	
	Mat img4;
	img4 = imread("lena.jpg");
	img4 = DrawPolygone(img4);
	
	namedWindow("Lena Color", cv::WINDOW_AUTOSIZE);
	imshow("Lena Color", img);
	namedWindow("Lena Gray", cv::WINDOW_AUTOSIZE);
	imshow("Lena Gray", gray);
	namedWindow("Lena Gray White Cross", cv::WINDOW_AUTOSIZE);
	imshow("Lena Gray White Cross", gray2);
	namedWindow("Lena Points", cv::WINDOW_AUTOSIZE);
	imshow("Lena Points", img2);
	namedWindow("Lena Red Cross", cv::WINDOW_AUTOSIZE);
	imshow("Lena Red Cross", img3);
	namedWindow("Lena Polygone", cv::WINDOW_AUTOSIZE);
	imshow("Lena Polygone", img4);
	waitKey(0);
	return 0;
}
