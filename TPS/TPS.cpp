# include "opencv2/highgui/highgui.hpp"
# include "opencv2/imgproc/imgproc.hpp"
# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <list>

using namespace cv;
using namespace std;

int thresh = 125;
Mat t1, t2;
list <Point> C1, C2;

void DrawCoins(Mat gray, int x){
	Mat dst, dst_norm, dst_norm_scaled;
	cornerHarris(gray, dst, 2, 3, 0.04, BORDER_DEFAULT );
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs(dst_norm, dst_norm_scaled );
	for( int j = 0; j < dst_norm.rows ; j++ ){
		for( int i = 0; i < dst_norm.cols; i++ ){
			if( (int) dst_norm.at<float>(j,i) > thresh ){
				Point P;
				P = Point(i,j);
				if(x == 1){
					circle(t1, Point(i,j), 5,  Scalar(0), 2, 8, 0 );
					C1.push_back(P);
				}
				if(x == 2) {
					circle(t2, Point(i,j), 5,  Scalar(0), 2, 8, 0 );
					C2.push_back(P);
				}
			}
		}
	}
}

int main( int argc, char** argv ){
	t1 = imread("t1.png");
	t2 = imread("t2.png");
	
	Mat gray1, gray2;
	cvtColor(t1, gray1, COLOR_RGB2GRAY);
	cvtColor(t2, gray2, COLOR_RGB2GRAY);
	
	DrawCoins(gray1, 1);
	DrawCoins(gray2, 2);
	
	imshow("corners_window1", t1);
	imshow("corners_window2", t2);
	
	waitKey(0);
	return 0;
}
