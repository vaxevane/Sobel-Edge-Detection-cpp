#include <iostream>
#include <fstream>
#include <string.h>

#include <mc_scverify.h>

//const int N = 288;
//const int M = 352;

void read(float read_image[N][M],char in_name[])
{
	FILE *frame_c;
	if((frame_c=fopen(in_name,"rb"))==NULL)
	{
		std::cout << "Image frame doesn't exist\n";

	}
	for(int  i = 0; i < N; i++)
	{
	    for(int j = 0; j < M; j++)
	    {
	      read_image[i][j] = fgetc(frame_c);
	    }	    
	}	
	fclose(frame_c);
}
void writeG(float write_image[N][M], char dir[], char out_name[])
{	
	FILE *frame_y;
	char* token = strtok(dir, ".");
	if (token != NULL) {
		strcat(token, out_name);
		frame_y = fopen(token, "wb");
	}
	

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			fputc(write_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write(float write_image[N][M], char dir[])
{
	FILE *frame_y;
	frame_y = fopen(dir, "wb");

	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			fputc(write_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write_all(float gradx[N][M], float grady[N][M], float oi[N][M], float oia[N][M],char dir[])
{
	writeG(gradx,dir,(char *)".Gx.yuv");
	writeG(grady,dir,(char *)".Gy.yuv");
	writeG(oi,dir,(char *)".G.yuv");
	writeG(oia,dir,(char *)".angle.yuv");
}
