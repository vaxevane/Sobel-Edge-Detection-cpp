#ifndef __SOBEL__
#define __SOBEL__

#include <iostream>
#include <ac_fixed.h>
#include <ac_math/ac_sqrt.h>
#include <ac_math/ac_atan2_cordic.h>
#include <mc_scverify.h>


typedef ac_fixed<18,8,false> root;
typedef ac_int<8,false> pixel;

const int N = 288;
const int M = 352;

void padding(pixel image[N][M]){
	
	//Preprocessing: making the bounds zero
	for (int i = 0; i < N; i++){
		image[i][0] = 0;
		image[i][M-1] = 0;
	}
	
	for (int j = 0; j < M; j++){
		image[0][j] = 0;
		image[N-1][j] = 0;		
	}
}
//pixel convolution(pixel window[N][M],int kernel[3][3]){
pixel convolution(pixel window[3][3],int kernel[3][3]){
	
    pixel sum = 0;
	for (int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		//	sum += window[i+row-1][j+col-1]*kernel[i][j]; //without sliding buff
			sum += window[i][j]*kernel[i][j];
		}
	}
	return sum;
}
#pragma hls_design top
void CCS_BLOCK(Sobel_algorithm)(pixel image[N][M], root Gx[N][M], root Gy[N][M], root edges[N][M],root angle[N][M]){

	int kx[3][3] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}};
	int ky[3][3] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};
	
	pixel window[3][3]; 
	typedef pixel linebuffer[M];
	linebuffer lb[2];
	
	root tempx,tempy,sq_sum,result;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			
			//Sliding window
			window[0][0] = window[0][1];
			window[1][0] = window[1][1];
			window[2][0] = window[2][1];
			
			window[0][1] = window[0][2];
			window[1][1] = window[1][2];
			window[2][1] = window[2][2];
			
			window[0][2] = lb[0][j];
			window[1][2] = (lb[0][j] = lb[1][j]);
			window[2][2] = (lb[1][j] = image[i][j]);

			if(i > 1 && j > 1){
				tempx = (Gx[i-1][j-1] = convolution(window, kx));
			    tempy =	(Gy[i-1][j-1] = convolution(window, ky));
				sq_sum = tempx*tempx +tempy*tempy;
		//		ac_math::ac_sqrt_pwl(sq_sum,result);
				ac_math::ac_sqrt(sq_sum,result);
				edges[i-1][j-1] = result;
		//		ac_math::ac_atan2_cordic(tempy,tempx,result);	
		//		angle[i-1][j-1] = result;
			}			
		}
	}
	
/*	for(int i = 1; i < N-1; i++){
		for(int j = 1; j< M-1; j++){
			tempx = (Gx[i-1][j-1] = convolution(window, kx));
			tempy = (Gy[i-1][j-1] = convolution(window, ky));
			sq_sum = tempx*tempx +tempy*tempy;
			ac_math::ac_sqrt_pwl(sq_sum,result);
			edges[i-1][j-1] = result;
			ac_math::ac_atan2_cordic(tempy,tempx,result);	
			angle[i-1][j-1] = result;
		}
	}*/
}

void min_max_normalization(root image[N][M]) {
	root min = 1000000, max = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if (image[i][j] < min) {
				min = image[i][j];
			}
			else if (image[i][j] > max) {
				max = image[i][j];
			}
		}
	}
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			root ratio = (root) (image[i][j] - min) / (max - min);
			image[i][j] = ratio * 255;
		}
	} 
}

void run_algorithm(pixel image[N][M], root Gx[N][M], root Gy[N][M], root edges[N][M],root angle[N][M]){
	
	
	std::cout<<"Preprocessing Image: By changing boundaries to zero"<< "\n";
	padding(image);
	
	std::cout<<"Running Sobel Algorithm for edge detection"<<"\n";
	
	Sobel_algorithm(image,Gx,Gy,edges,angle);
	
	std::cout<<"Filtering each Gradient in order to improve the results"<<"\n\n";
	min_max_normalization(Gx);
	min_max_normalization(Gy);
	min_max_normalization(edges);
	
}
#endif
