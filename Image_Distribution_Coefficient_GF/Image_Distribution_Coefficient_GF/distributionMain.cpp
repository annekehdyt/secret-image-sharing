#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include "SScoefficient.h"
#include "GFheader.h"

#define COLUMN 256
#define ROW	256

using namespace std;
using namespace cv;

void dist_img(string imgName, int t, int n, string name);

/*
	CV_8UC1 
	8-bit unsigned
	C1 One channel (For grayscale image)
*/

void main(){
	dist_img("256_Peppers.bmp", 3,10, "Peppers");
	//dist_img("cameraman.bmp", 8,10);

	waitKey(0);
}

/**
	dist_img

	t : threshold value
	n : Total value
	secret	: zero value array to put the pixels
**/
void dist_img(string img, int t, int n, string name){
	Mat image = imread(img, CV_LOAD_IMAGE_GRAYSCALE);
	Mat imshare[20];

	String imgName;
	string display;

	int i,j,l;
	int a=0,b=0;
	int c_index,r_index,sParam=0;

	int *share;
	int *secret;

	share = static_cast<int *>(malloc(n * sizeof(int)));
	secret = static_cast<int *>(malloc(t * sizeof(int)));
	 
	c_index = image.cols/t;
	r_index = image.rows%t;
	if(r_index>0)
		r_index = r_index + image.rows + 1;
	else
		r_index = image.rows;

	if(! image.data){
		cout << "Could not open or find the image" << std::endl;
	}

	for(i=0; i<n; i++){
		imshare[i] = Mat(r_index,c_index, CV_8UC1);
	}

	/***
		img.at<uchar>(y,x)
		y	: row index
		x	: column index
	**/

	for(i = 0; i<image.rows; i++){
		for(j=0; j<image.cols; j++){
			secret[sParam++] = image.at<uchar>(i,j);
			
			if(i == (image.rows-1) && j == (image.cols-1) && sParam < t){
				
				for(l=sParam; l<t; l++){
					secret[l] = 0;
				}
				sParam = t;
				
			}

			if(sParam == t){
				polynomial(secret, t, n, share);

				for(l=0; l<n; l++){
					imshare[l].at<uchar>(a,b) = share[l];
				}
				b++;
				if(b == c_index){
						b=0;
						a++;
				} 
				sParam = 0;
			}


				
		}
	}

	/**** Polynomial secret *****/

	
	for(i=0; i<n; i++){
		imgName = "./" + name + "/imshare_" + std::to_string((long long int)i+1) + ".bmp";
		imwrite(imgName, imshare[i]);
	}

	/****	DISPLAY
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	for(i=0; i<n; i++){
		display = "Display Window " + std::to_string((long long int)i+1);
		namedWindow(display, WINDOW_AUTOSIZE);
		imshow(display, imshare[i]);
	}*/

	free(share);
	free(secret);
}


