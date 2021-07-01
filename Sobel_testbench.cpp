#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>

#include "Sobel.h"
#include "yuv_io.h"

int main(){
	
	float image[N][M],gx[N][M],gy[N][M],out_image[N][M],out_image_angle[N][M];
	int check_array[5] = {0, 0, 0, 0, 0};
	char indir[50],outdir[50],checkdir[50];
	int corr_count,mode;
	
	std::cout << "Choose Mode: (0) Produce Check Mode or (1) Test Mode \n"; 
	std::cin >> mode;
	
	srand (time(NULL));
	//Finding the Edges for 5 out of 10 (random)
	for (int i = 0; i < 5; i++){
		
		int  pic = rand() % 10 + 1;
//		std::cout << pic << " ";
		//Find always a diff image
		while(check_array[i] == 0){
		int val = 0;
			for(int j = 0; j <= i; j++){
				if(check_array[j] == pic){
					val = check_array[j];
				//	std::cout << "SAMEEE ";
				}
			}
			if(val == pic){
				//Picking new random image
				pic = rand() % 10 + 1;
			}else{
				check_array[i] = pic;
			}
		}
		if (mode == 1){
			std::cout << "Comparing the output with the existing Check Samples for the ";
		}else{
			std::cout << "Creating Check Samples for the ";
		}
		switch (pic) {
			case 1:
				std::cout << "Akiyo Image\n";
				strcpy(indir,"Input/akiyo_cif_0_yuv420.yuv");
				strcpy(checkdir,"Check/akiyo.yuv");
				strcpy(outdir,"Output/akiyo");
				break;
			case 2:
				std::cout << "Blackdog Image\n";
				strcpy(indir,"Input/Blackdog.yuv");
				strcpy(checkdir,"Check/blackdog.yuv");
				strcpy(outdir,"Output/blackdog");
				break;
			case 3:
				std::cout << "First Bus Image\n";
				strcpy(indir,"Input/bus_cif_0_yuv420.yuv");
				strcpy(checkdir,"Check/bus1.yuv");
				strcpy(outdir,"Output/bus1");				
				break;
			case 4:
				std::cout << "Second Bus Image\n";
				strcpy(indir,"Input/bus_cif_99_yuv420.yuv");
				strcpy(checkdir,"Check/bus2.yuv");
				strcpy(outdir,"Output/bus2");				
				break;
			case 5:
				std::cout << "Coastguard Image\n";
				strcpy(indir,"Input/coastguard_cif_99_yuv420.yuv");
				strcpy(checkdir,"Check/coast.yuv");
				strcpy(outdir,"Output/coast");				
				break;
			case 6:
				std::cout << "Container Image\n";
				strcpy(indir,"Input/container_cif_180_yuv420.yuv");
				strcpy(checkdir,"Check/container.yuv");
				strcpy(outdir,"Output/container");
				break;
			case 7:
				std::cout << "Flower Image\n";
				strcpy(indir,"Input/flower_cif_0_yuv420.yuv");
				strcpy(checkdir,"Check/flower.yuv");
				strcpy(outdir,"Output/flower");
				break;
			case 8:
				std::cout << "Foreman Image\n";
				strcpy(indir,"Input/foreman_cif_90_yuv420.yuv");
				strcpy(checkdir,"Check/foreman.yuv");
				strcpy(outdir,"Output/foreman");
				break;
			case 9:
				std::cout << "Lena Image\n";
				strcpy(indir,"Input/lena.yuv");
				strcpy(checkdir,"Check/lena.yuv");
				strcpy(outdir,"Output/lena");
				break;
			case 10:
				std::cout << "Parrots Image\n";
				strcpy(indir,"Input/Parrots.yuv");
				strcpy(checkdir,"Check/parrots.yuv");
				strcpy(outdir,"Output/parrots");
				break;
		}
	//Reading initial image
	read(image,indir);

	//Running Algorithm
	run_algorithm(image,gx,gy,out_image,out_image_angle);

	if(mode == 1){
		//Reusing image to read the check values USE AFTER CREATING THE FIRST CHECK FILES
		read(image,checkdir);
		//Checking if the edge detection algorithm is correct
		corr_count = 0;
		for(int n = 0; n < N; n++){
			for(int m = 0; m < M; m++){
	//			std::cout << truncf(out_image[n][m]) << " " << image[n][m];
	//			std::cout << "\n";
				if(truncf(out_image[n][m]) == image[n][m]){
					corr_count++;
				} 
			}
		}
	}
	//Write back the results on the Output file
	write_all(gx,gy,out_image,out_image_angle,outdir);
	
	if(mode == 0){
		//Before testing write the edges for checking
		write(out_image,checkdir);
	}
	
	}

	return 0;
}
