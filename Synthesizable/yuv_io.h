#include <iostream>
#include <fstream>
#include <string.h>

#include <mc_scverify.h>

const int H = 288;
const int WI = 352;

void read(int in_image[H][WI],char in_name[]);

void writeG(int out_image[H][WI], char dir[], char out_name[]);

void write(int out_image[H][WI], char dir[]);

void write_all(int gx[H][WI], int gy[H][WI], int oi[H][WI], int oia[H][WI],char dir[]);
