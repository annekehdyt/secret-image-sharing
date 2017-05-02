/**********************************

Wednesday 2015.01.21
Anneke Soraya Hidayat

***********************************/

#include <iostream>
#include <fstream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void polynomial(int secret[], int t, int n, int *shares);
void reconstruction(int t_share, int shares[][2], int final[]);

void swap(int *left, int *middle, int degree);
void convolution(int left[], int right[], int *middle, int degree);
int multiInv(int num, int prime);

/****
*
	Tulis Keterangan




*/