#include <fstream>
#include <string.h>


void read(float in_image[N][M],char in_name[])
{
	FILE *frame_c;
	if((frame_c=fopen(in_name,"rb"))==NULL)
	{
		printf("image frame doesn't exist\n");
		exit(-1);
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
void write(float out_image[N][M], char dir[], char out_name[])
{	
	FILE *frame_y;
	char* token = strtok(dir, ".");
	if (token != NULL) {
		strcat(token, out_name);
		frame_y = fopen(token, "wb");
	}
	

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			fputc(out_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write(float out_image[N][M], char dir[])
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
void write_all(float gx[N][M], float gy[N][M], float oi[N][M], float oia[N][M],char dir[])
{
	write(gx,dir,(char *)".Gx.yuv");
	write(gy,dir,(char *)".Gy.yuv");
	write(oi,dir,(char *)".G.yuv");
	write(oia,dir,(char *)".angle.yuv");
}
