#include <iostream>
#include <cmath>

const int N = 288;
const int M = 352;
const int W = 3;

void padding(float image[N][M]){
	
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

//float convolution(float window[N][M],float kernel[W][W]){
float convolution(float window[W][W],float kernel[W][W]){
	
	int sum = 0;
	for (int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
		//	sum += window[i+row-1][j+col-1]*kernel[i][j]; //without sliding buff
			sum += window[i][j]*kernel[i][j];
		}
	}
	return sum;
}

void Sobel_algorithm(float image[N][M], float Gx[N][M], float Gy[N][M], float edges[N][M],float angle[N][M]){

	float kx[W][W] = {{0, 0, 0},{-2, 0, 2},{-1, 0, 1}};
	float ky[W][W] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};
	
	float window[W][W]; 
	typedef short linebuffer[M];
	linebuffer lb[2];
	
	float tempx,tempy,sq_sum;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			
			//Sliding window
			for (int l=0; l < W; l++) {
				window[0][l] = (l==W-1) ? lb[0][j] : window[0][l+1];
				window[1][l] = (l==W-1) ? lb[1][j] : window[1][l+1];
				window[2][l] = (l==W-1) ? image[i][j]: window[2][l+1];
			}
			lb[0][j]=lb[1][j];
			lb[1][j]=image[i][j];	

			if(i > 1 && j > 1){
				tempx = (Gx[i-1][j-1] = convolution(window, kx));
			    tempy =	(Gy[i-1][j-1] = convolution(window, ky));
				sq_sum = tempx*tempx +tempy*tempy;
				edges[i-1][j-1] = sqrt(sq_sum);
				angle[i-1][j-1] = atan2(tempy,tempx);	
			}			
		}
	}
	
/*	for(int i = 1; i < N-1; i++){
		for(int j = 1; j< M-1; j++){
			tempx = (Gx[i-1][j-1] = convolution(window, kx));
			tempy = (Gy[i-1][j-1] = convolution(window, ky));
			sq_sum = tempx*tempx +tempy*tempy;
			edges[i-1][j-1] = sqrt(sq_sum);
			angle[i-1][j-1] = atan2(tempy,tempx);	
		}
	}*/
}

void min_max_normalization(float image[N][M]) {
	float min = 1000000, max = 0;
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < M; j++) {
			if (image[i][j] < min) {
				min = image[i][j];
			}
			else if (image[i][j] > max) {
				max = image[i][j];
			}
		}
	}
	
	for(i = 0; i < N; i++) {
		for(j = 0; j < M; j++) {
			float ratio = (float) (image[i][j] - min) / (max - min);
			image[i][j] = ratio * 255;
		}
	} 
}

void run_algorithm(float image[N][M], float Gx[N][M], float Gy[N][M], float edges[N][M],float angle[N][M]){
	
	
	std::cout<<"Preprocessing Image: By changing boundaries to zero"<< "\n";
	padding(image);
	
	std::cout<<"Running Sobel Algorithm for edge detection"<<"\n";
	
	Sobel_algorithm(image,Gx,Gy,edges,angle);
	
	std::cout<<"Filtering each Gradient in order to improve the results"<<"\n\n";
	min_max_normalization(Gx);
	min_max_normalization(Gy);
	min_max_normalization(edges);
	
}
