# include "opencv2/imgproc/imgproc.hpp"
# include "opencv2/highgui/highgui.hpp"
# include <stdlib.h>
# include <stdio.h>
# include <opencv2/opencv.hpp>
# include <iostream>

using namespace std;
using namespace cv;

Mat img, gray;

int main( int argc, char** argv ){
	img = imread("coins.jpg");
	
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray,gray,40,255,0);
	namedWindow("Coins", WINDOW_AUTOSIZE );
	imshow("Coins", gray);
	waitKey(0);
	
	Mat dist;
	distanceTransform(gray,dist,DIST_L2,3);
	normalize(dist, dist, 0, 1., NORM_MINMAX);
	namedWindow("Coins distance", WINDOW_AUTOSIZE );
	imshow("Coins distance", dist);
	waitKey(0);
	
	Mat distBin;
	threshold(dist, distBin, .5, 1., 0);
	namedWindow("Coins distance Binary", WINDOW_AUTOSIZE );
	imshow("Coins distance Binary", distBin);
	waitKey(0);
	
	Mat dist_8u;
	dist.convertTo(dist_8u, 8U);
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int ncomp = static_cast<int>(contours.size());
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);
    
    for (int i = 0; i < ncomp; i++){
		drawContours(markers, contours, i, Scalar::all(i+1), -1);
	}
    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);
    namedWindow("Markers", WINDOW_AUTOSIZE );
    imshow("Markers", markers*10000);
	waitKey(0);
	
	watershed(img, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark);
	vector<Vec3b> colors;
    for (size_t i = 0; i < contours.size(); i++) {
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
			int index = markers.at<int>(i,j);
			if (index > 0 && index <= static_cast<int>(contours.size())){
				dst.at<Vec3b>(i,j) = colors[index-1];
			}
            else dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
		}
	}
	namedWindow("Final Result", WINDOW_AUTOSIZE );
    imshow("Final Result", dst);
    waitKey(0);
	
	return 0;
}
