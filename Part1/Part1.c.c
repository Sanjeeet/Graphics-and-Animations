#include <stdlib.h>

void draw_line(int x0, int x1, int y0, int y1);
void swapValues(int* a, int* b);
void drawPixel(int x, int y, short colour);
void clearScreen();

int main (){
	
	clearScreen();
	
	draw_line(1,42, 1, 35);
	draw_line(1,100, 10, 10);
	draw_line(0,0, 1, 35);
	draw_line(42,1, 35, 1);
	
	while (1) ;
}

//function for clearing screen to black
void clearScreen(){
	int i, j;
	for (i = 0; i < 320; i++){
		for (j = 0; j < 240; j++){
			drawPixel(i, j, 0); //draw at every pixel with colour black
		}		
	}
	
}

//function for drawing line using Brensenhams algorithm
void draw_line(int x0, int x1, int y0, int y1){
	
	int isSteep = (abs(y1 - y0) > abs(x1 - x0));
	if (isSteep){
		swapValues(&x0, &y0);
		swapValues(&x1, &y1);
	}
	if (x0 > x1){
		swapValues(&x0, &x1);
		swapValues(&y0, &y1);
	}
	
	int deltax = x1 - x0;
	int deltay = abs(y1 - y0);
	int error = -(deltax/2);
	
	int y = y0;
	int yStep;
	if (y0 < y1)
		yStep = 1;
	else
		yStep = -1;
	
	int x;
	for (x = x0; x <= x1; x++){
		if (isSteep)
			drawPixel(y, x, 0xFFFF);
		else
			drawPixel(x, y, 0XFFFF);
		error = error + deltay;
		if (error > 0){
			y = y + yStep;
			error = error - deltax;
		}
		
	}
}

//function for drawing pixel
void drawPixel(int x, int y, short colour){
	volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
	*vga_addr=colour;

}

//function for swaping variables
void swapValues(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
	
}