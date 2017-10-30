#include <stdlib.h>
#include <math.h>

void draw_line(int x0, int x1, int y0, int y1, short colour);
void swapValues(int* a, int* b);
void drawPixel(int x, int y, short colour);
void clearScreen();

int main (){
	
	clearScreen();
	
	//float twoDegreeInRad = (M_PI/180) * 2;
	
	//draw_line(0,0, 0, 30);
	
	//initial position
	int x0 = 160; 
	double x1 = 20;
	int y0 = 120;
	double y1 = 0; 
	int direction = 1;
	
	draw_line(x0,160 + x1,y0, 120 - y1, 0xFFFF);
	
	int counter = 0;
	
	while (1) {
		//poll status register
		volatile int* statusRegister = (volatile int *)(0xFF20302C);
		volatile int status = *statusRegister & 0x1; //read the first bit of the status register
		if (status == 0){
			draw_line(x0, (int) (160 + round(x1)),y0, (int) (120 - round(y1)), 0x0000);
			
			if (counter == 180){
				x1 = 20;
				y1 = 0;
				counter = 0;
			}
			else{
			
				x1 = (x1 * cos ((M_PI/180) * 2)) - (y1 * sin((M_PI/180) * 2));
				y1 = (x1 * sin ((M_PI/180) * 2)) + (y1 * cos((M_PI/180) * 2));
				counter++;
			}
			draw_line(x0, (int)(160 + round(x1)),y0, (int)(120 - round(y1)), 0xFFFF);
			
			volatile short *vga_buffer = (volatile short*)(0xFF203020);
			*vga_buffer=1;
			
		}
		
	}
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
void draw_line(int x0, int x1, int y0, int y1, short colour){
	
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
			drawPixel(y, x, colour);
		else
			drawPixel(x, y, colour);
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