#include "Sobel.h"
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
//conv convolution(pixel window[N][M],int kernel[W][W],int row,int col){
conv convolution(pixel window[W][W],int kernel[W][W]){
	
	int sum = 0;
	CONVX:for (int i = 0; i < 3; i++){
		CONVY:for(int j = 0; j < 3; j++){
		//	sum += window[i+row-1][j+col-1]*kernel[i][j]; //without sliding buff
			sum += window[i][j]*kernel[i][j];
		}
	}
	return sum;
}

#pragma hls_design top
void CCS_BLOCK(Sobel_algorithm)(pixel image[N][M], conv Gx[N][M], conv Gy[N][M], grd edges[N][M],ac_int<11,true> angle[N][M]){

	int kx[W][W] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}};
	int ky[W][W] = {{1, 2, 1},{0, 0, 0},{-1, -2, -1}};
	
	pixel window[W][W]; 
	typedef pixel linebuffer[M];
	linebuffer lb[2];
	
	conv tx,ty;
	sq sqx,sqy;
	root sq_sum;
	ac_fixed<16,11,false> result;
	ang resul;
	
	IMAGEX:for (int i = 0; i < N; i++) {
		IMAGEY:for (int j = 0; j < M; j++) {
			
			//Sliding window
			WIND:for (int l=0; l < W; l++) {
				window[0][l] = (l==W-1) ? lb[0][j] : window[0][l+1];
				window[1][l] = (l==W-1) ? lb[1][j] : window[1][l+1];
				window[2][l] = (l==W-1) ? image[i][j]: window[2][l+1];
			}
			lb[0][j]=lb[1][j];
			lb[1][j]=image[i][j];	

			if(i > 1 && j > 1){
				tx = (Gx[i-1][j-1] = convolution(window, kx));
			    ty = (Gy[i-1][j-1] = convolution(window, ky));
			    sqx = tx * tx;
			    sqy = ty * ty;
				sq_sum = sqx + sqy;
				ac_math::ac_sqrt(sq_sum,result);
				edges[i-1][j-1] = result.to_uint();
				ac_math::ac_atan2_cordic((ac_fixed<9,11>)ty,(ac_fixed<9,11>)tx,resul);
				angle[i-1][j-1] = resul.to_int();
			}			
		}
	}
	
	/*IMAGEX:for(int i = 1; i < N-1; i++){
		IMAGEY:for(int j = 1; j< M-1; j++){
			tx = (Gx[i-1][j-1] = convolution(image, kx, i, j));
			ty = (Gy[i-1][j-1] = convolution(image, ky, i, j));
			sqx = tx * tx;
			sqy = ty * ty;
			sq_sum = sqx + sqy;
			ac_math::ac_sqrt(sq_sum,result);
			edges[i-1][j-1] = result.to_uint();
			ac_math::ac_atan2_cordic((ac_fixed<9,11>)ty,(ac_fixed<9,11>)tx,resul);	
			angle[i-1][j-1] = resul.to_int();	
		}
	}*/
	
}

void min_max_normalization(int image[N][M]) {
	int min = 1000000, max = 0;
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
			float ratio = float (image[i][j] - min) / (max - min);
			image[i][j] = ratio * 255;
		}
	} 
}

void run_algorithm(int image[N][M], int Gx[N][M], int Gy[N][M], int edges[N][M],int angle[N][M]){
	
	pixel pixelimage[N][M];
	conv Gradx[N][M],Grady[N][M];
	grd Grad[N][M];
	ac_int<11,true> Angle[N][M];
	
	for (int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			pixelimage[i][j] = image[i][j];
		}
	}
	std::cout<<"Preprocessing Image: By changing boundaries to zero"<< "\n";
	padding(pixelimage);
	
	std::cout<<"Running Sobel Algorithm for edge detection"<<"\n";
	Sobel_algorithm(pixelimage,Gradx,Grady,Grad,Angle);
	
	for(int i = 0; i < N; i++){
		for (int j = 0; j < M; j++){
			Gx[i][j] = Gradx[i][j];
			Gy[i][j] = Grady[i][j];
			edges[i][j] = Grad[i][j];
			angle[i][j] = Angle[i][j];
		}
	}
	
	std::cout<<"Filtering each Gradient in order to improve the results"<<"\n\n";
	min_max_normalization(Gx);
	min_max_normalization(Gy);
	min_max_normalization(edges);
	
}
