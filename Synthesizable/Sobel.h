//Sobel.h
#ifndef __SOBEL__
#define __SOBEL__

#include <iostream>
#include <ac_fixed.h>
#include <ac_math/ac_sqrt.h>
#include <ac_math/ac_atan2_cordic.h>
#include <mc_scverify.h>



typedef ac_int<8,false> pixel;
typedef ac_int<11,true> conv;
typedef ac_int<20,false> sq;
typedef ac_fixed<14,21,false> root;
typedef ac_int<11,false> grd;
typedef ac_fixed<8,3,true> ang;


const int N = 288;
const int M = 352;
const int W = 3;

void padding(pixel image[N][M]);

//conv convolution(pixel window[N][M],int kernel[W][W],int row, int col);

conv convolution(pixel window[W][W],int kernel[W][W]);

void Sobel_algorithm(pixel image[N][M], conv Gx[N][M], conv Gy[N][M], grd edges[N][M],ang angle[N][M]);

void min_max_normalization(int image[N][M]);

void run_algorithm(int image[N][M], int Gx[N][M], int Gy[N][M], int edges[N][M],int angle[N][M]);

#endif
