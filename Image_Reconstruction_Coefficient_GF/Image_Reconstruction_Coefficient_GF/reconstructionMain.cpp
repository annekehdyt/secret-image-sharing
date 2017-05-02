#include "stdafx.h"
//#include "imageUtil.h"
#include "SScoefficient.h"
#include "GFheader.h"
#include <iostream>
#include <fstream>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>

#define T_VALUE 2
#define PRIME 251 


using namespace std;
using namespace cv;

void polynomial(int secret[], int t, int n, int *shares, int prime);
void reconstruction(int t_share, int shares[][2], int final[], int prime);

void swap(int *left, int *middle, int degree);
void convolution(int left[], int right[], int *middle, int degree);
int multiInv(int num, int prime);
static string BMSHARES[10] = {"imshare_1.bmp", "imshare_2.bmp", "imshare_3.bmp", "imshare_4.bmp" , "imshare_5.bmp",
							  "imshare_6.bmp", "imshare_7.bmp", "imshare_8.bmp", "imshare_9.bmp", "imshare_10.bmp"};


void main(){
	int img[10] = {1,2,3};
	int m = 3;
	int final[10]={};
	int i,j, k,l,value;
	int row=0, col=0;
	int shares[10][2];
	Mat imshare[10];

	for(int i=0; i<m; i++){
		imshare[i] = imread(BMSHARES[img[i]-1], CV_LOAD_IMAGE_GRAYSCALE);
		shares[i][0] = img[i];
	}

	Mat imcover(256,256, CV_8UC1);
	
	for(i = 0; i<imshare[0].rows; i++){
		for(j=0; j<imshare[0].cols; j=j++){
			for(k=0; k<m; k++){
				shares[k][1] = imshare[k].at<uchar>(i,j);
			}


			reconstruction(m, shares, final);
			

			/////////////////////////
			for(l=(m-1); l>=0; l--){
				imcover.at<uchar>(row,col++) = final[l];
				final[l] = 0;
				
				cout << i << " , " << j << " , " << k << " ======== " << row << " , " << col << endl;

				if(col == imcover.cols){
					col=0;
					row++;
				}
			}
		}
	}

	imwrite("imcover.bmp", imcover);

	namedWindow("Display window_1", WINDOW_AUTOSIZE);
	imshow("Display window_1", imshare[0]);

	namedWindow("Display window_2", WINDOW_AUTOSIZE);
	imshow("Display window_2", imshare[1]);

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", imcover);

	waitKey(0);
}
