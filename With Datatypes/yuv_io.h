#include <fstream>
#include <string.h>
#include <ac_fixed.h>
#include <mc_scverify.h>

typedef ac_fixed<19,19,false> root;
//typedef ac_int<9,true> grad;
typedef ac_int<8,false> pixel;
//typedef ac_int<9,false> pixed_out;
//typedef ac_int<18,false> square;

//const int N = 288;
//const int M = 352;

void read(int in_image[N][M],char in_name[])
{
	FILE *frame_c;
	if((frame_c=fopen(in_name,"rb"))==NULL)
	{
		printf("image frame doesn't exist\n");
		
	}
	for(int  i = 0; i < N; i++)
	{
	    for(int j = 0; j < M; j++)
	    {
	      in_image[i][j] = fgetc(frame_c);
	    }	    
	}	
	fclose(frame_c);
}
void writee(int out_image[N][M], char dir[], char out_name[])
{	
	FILE *frame_y;
	char* token = strtok(dir, ".");
	if (token != NULL) {
		strcat(token, out_name);
		frame_y = fopen(token, "wb");
	}
	

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			fputc((int)out_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write(int out_image[N][M], char dir[])
{
	FILE *frame_y;
	frame_y = fopen(dir, "wb");

	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			fputc(out_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write_all(int gx[N][M], int gy[N][M], int oi[N][M], int oia[N][M],char dir[])
{
	writee(gx,dir,(char *)".Gx.yuv");
	writee(gy,dir,(char *)".Gy.yuv");
	writee(oi,dir,(char *)".G.yuv");
	writee(oia,dir,(char *)".angle.yuv");
}
