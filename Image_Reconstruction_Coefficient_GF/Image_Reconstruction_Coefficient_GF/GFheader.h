/**********************************

Tuesday 2014.12.16
Anneke Soraya Hidayat

***********************************/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

unsigned short modGF(unsigned short y);
unsigned short addSubGF(unsigned short num1, unsigned short num2);
unsigned short multiGF(unsigned short num1, unsigned short num2);
unsigned short multiInvGF(unsigned short num);
unsigned short powerGF(unsigned short num1, unsigned short num2);

unsigned short bitSize(unsigned short num);
unsigned short nBit(unsigned short num);
unsigned short inv_nBit(unsigned short num);

void polyBit(unsigned short *polyBit, unsigned short num);
BOOL isBit(unsigned short num, unsigned short N);


/*
*
*	modGF		: Modular Over GF(2^8)
*	addSubGF	: Addition and Subtraction over GF(2^8)
*	multiGF		: Multiplication over GF(2^8)
*	multiInvGF	: Multiplicative Inverse over GF(2^8)
*	powerGF		: Power multiplication over GF(2^8)
*
*	Additional Funtion
*	
*	bitSize		: Return the location of MSB (Most Significant Bit)
*	nBit		: Return the bit position ( Ex. 4 = 0100. The return value is 3)
*	inv_nBit	: Return the bit value (Ex. 3. The return value is 4 = 0100)
*	polyBit		: Return the polynomial form in array
*	isBit		: Return the boolean value of N'th bit. 1 or 0.
*
*/