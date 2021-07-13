#include "yuv_io.h"

void read(int in_image[H][WI],char in_name[])
{
	FILE *frame_c;
	if((frame_c=fopen(in_name,"rb"))==NULL)
	{
		std::cout << "Image frame doesn't exist\n";
		//exit(-1);
	}
	for(int  i = 0; i < H; i++)
	{
	    for(int j = 0; j < WI; j++)
	    {
	      in_image[i][j] = fgetc(frame_c);
	    }	    
	}	
	fclose(frame_c);
}
void writeG(int out_image[H][WI], char dir[], char out_name[])
{	
	FILE *frame_y;
	char* token = strtok(dir, ".");
	if (token != NULL) {
		strcat(token, out_name);
		frame_y = fopen(token, "wb");
	}
	

	for(int i = 0; i < H; i++){
		for(int j = 0; j < WI; j++){
			fputc(out_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write(int out_image[H][WI], char dir[])
{
	FILE *frame_y;
	frame_y = fopen(dir, "wb");

	
	for(int i = 0; i < H; i++){
		for(int j = 0; j < WI; j++){
			fputc(out_image[i][j],frame_y);
		}
	}
	fclose(frame_y);
}
void write_all(int gx[H][WI], int gy[H][WI], int oi[H][WI], int oia[H][WI],char dir[])
{
	writeG(gx,dir,(char *)".Gx.yuv");
	writeG(gy,dir,(char *)".Gy.yuv");
	writeG(oi,dir,(char *)".G.yuv");
	writeG(oia,dir,(char *)".angle.yuv");
}
