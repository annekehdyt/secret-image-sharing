/**********************************

Tuesday 2014.12.16
Anneke Soraya Hidayat

***********************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "GFheader.h"

/*
*	Addition and Subtraction over GF(2^8)
*/
unsigned short addSubGF(unsigned short num1, unsigned short num2){
	return num1^num2;
}


/*
	Multiplication over GF(2^8)
*/
unsigned short multiGF(unsigned short num1, unsigned short num2){
	unsigned short result=0;
	unsigned short poly1[16]={0}, poly2[16]={0};
	unsigned short poly[16]={0};
	unsigned short int i,j, temp;

	polyBit(poly1, num1);
	polyBit(poly2, num2);

	for(i=0; i<bitSize(num1); i++){

		if(poly1[i] == 0)
			continue;

		for(j=0; j<bitSize(num2); j++){
			if(poly2[j] == 0)
				continue;

			temp = i + j;
			poly[temp]++;
		}
	}

	for(i=0; i<16; i++){
		if(poly[i] % 2 == 0)
			poly[i] = 0;
		else
			result = result | inv_nBit(i+1);
	}
	 
	return modGF(result);
}

/*
	Return the power of num1
*/
unsigned short powerGF(unsigned short num1, unsigned short num2){
	unsigned short res=num1, i;

	for(i=0; i<num2-1; i++){
		res = multiGF(res, num1);
	}

	return res;
}

/*
	Change number into polynomial form

	Param
	polybit : The array pointer
	num		: The input number
*/
void polyBit(unsigned short *polyBit, unsigned short num){
	unsigned short i;
	unsigned short len1;
	unsigned short temp, param;

	len1 = 16;

	temp = 0;
	param = 1;
	i = 0;
	
	while(temp < 256){
		temp = 0;
		temp = num & param;

		if(temp == param){
			polyBit[i] = TRUE;
		}else
			polyBit[i] = FALSE;

		if(i == (len1-1))
			break;

		param = param << 1;
		i++;
	}
	
}

/*
	Modular calculation over GF(2^8)

	Input : number
	Output : Remainder
*/

unsigned short modGF(unsigned short y){
	if(y >= 32768)
		y=y^0x8d80; // >=32768
	else if(y >= 16384)
		y=y^0x46C0; // >=16384
	else if(y >= 8192)
		y=y^0x2360; // >=8192
	else if(y >= 4096)	
		y=y^0x11B0; // >=4096
	else if(y >= 2048)
		y=y^0x08d8; // >=2048
	else if(y >= 1024)
		y=y^0x046C; // >=1024
	else if(y >= 512)
		y=y^0x0236; // >=512
	else if(y >= 256)
		y=y^0x011B; // >=256

	if(y>=256)
		return modGF(y);
	else
		return y;
}

/**
	Provide the multiplicative Inverse over GF(2^8)
**/
unsigned short multiInvGF(unsigned short num){
	
	unsigned char Q, Q1, flag;
	unsigned short C1;
	unsigned short A2, B2, C2, nextB2;
	unsigned short A3, B3;
	unsigned short N, temp;

	C1 = 0;
	C2 = 0;
	A2 = 0;
	B2 = 0;
	A3 = 283;
	B3 = num;
	N = 0;
	flag = FALSE;
	nextB2 = 0;
	
	if(B3 == 1)
		return 1;

	while(B3 > 1){
		Q = 0;
		temp = B3;
		do{
			Q1 =1;
			while(bitSize(A3) != bitSize(B3)){
				B3 = B3 << 1;
				Q1 = Q1 * 2;
			}					

			Q = Q + Q1; 
			A3 = A3 ^ B3;
			B3 = temp;

		}while(A3 > temp || bitSize(A3) > bitSize(temp));						
		
		A2 = nextB2;
		if(flag == FALSE){
			B2 = 1;
			flag = TRUE;
		}
			
		B3 = A3;				
		A3 = temp;
		N = bitSize(Q);
		temp = B2;
		C2 = 0;

		/*** The End of Step 1 ***/

		while(N > 0){

			if(isBit(Q, N) == TRUE){
				nextB2 = B2;
				C1 = B2 << (N-1);
				C2 = C2 ^ C1;
			}
			N--;
		}

		B2 = C2;
		B2 = B2 ^ A2;
		A2 = temp;
	}

	return B2;
}

/**
	Calculate the bit Size. (The MSB position)
**/
unsigned short bitSize(unsigned short num){
	unsigned short param;
	unsigned short temp;
	unsigned short flag;

	temp = 0;
	flag = 0;
	param = 256;

	while(flag == 0){
		temp = num & param;

		if(temp == param){
			flag = 1;
			break;
		}

		param = param >> 1;
		temp = 0;
	}
	return nBit(param);
}

/**
	Check the N'th bit is 1 or not
**/
BOOL isBit(unsigned short num, unsigned short N){
	unsigned short param;
	unsigned short temp;

	param = inv_nBit(N);

	temp = num & param;

	if(param == temp)
		return TRUE;
	else
		return FALSE;
}

/*
	Change the bit value into bit position
*/
unsigned short nBit(unsigned short num){
	if(num == 256) return 9;
	else if(num == 128) return 8;
	else if(num == 64) return 7;
	else if(num == 32) return 6;
	else if(num == 16) return 5;
	else if(num == 8) return 4;
	else if(num == 4) return 3;
	else if(num == 2) return 2;
	else if(num == 1) return 1;
	else return 0;
}

/*
	Change the bit position into bit value
*/
unsigned short inv_nBit(unsigned short num){
	if(num == 1) return 1;
	else if(num == 2) return 2;
	else if(num == 3) return 4;
	else if(num == 4) return 8;
	else if(num == 5) return 16;
	else if(num == 6) return 32;
	else if(num == 7) return 64;
	else if(num == 8) return 128;
	else if(num == 9) return 256;
	else if(num == 10) return 512;
	else if(num == 11) return 1024;
	else if(num == 12) return 2048;
	else if(num == 13) return 4096;
	else if(num == 14) return 8192;
	else if(num == 15) return 16384;
	else if(num == 16) return 32768;
	else return 0;
}
