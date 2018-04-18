/*
  Author: Alessandra Vertrees
  Course: CSCI-136
  Instructor: Nick Crister
  Assignment: Lab 9F

  Description:
    The program reads a PGM image from the file "inImage.pgm",
    and outputs a pixelated version of "inImage.pgm" to "outImage.pgm". 

  Compile command: g++ pixelate.cpp -o pixelate
  Run command: ./pixelate
  Open image: eog outImage.pgm
*/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

void readImage(int image[MAX_H][MAX_W], int &height, int &width);
void writeImage(int image[MAX_H][MAX_W], int height, int width);    

int main() {

	int img[MAX_H][MAX_W];
	int h, w;

	readImage(img, h, w); // read it from the file "inImage.pgm"
	// h and w were passed by reference and
	// now contain the dimensions of the picture
	// and the 2-dimesional array img contains the image data

	// Now we can manipulate the image the way we like
	// for example we copy its contents into a new array

	int out[MAX_H][MAX_W];
    int hb = MAX_H;
    int wb = MAX_W; 

	for(int row = 0; row < hb; (row = row + 2 )) {
		for(int col = 0; col < wb; ( col = col + 2)) {
			//get average of 2x2 pixel square:
			// declare x, xb, y, yb for coordinates of square to calc average
			// col*2 indicates each corner of the 2x2 square
			int x = col;
			int y = row;
			int xb = x+1;
			int yb = y+1;
			// int avg = (TL + TR + BL + BR ) / 4
			int aveColor = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
			//if 0,0 or both col and row are divisable by 2
			// store value of 2x2 pixel square in outImage to the average value that was calculated above
			//new row and col variables

			if( ((col == 0) && (row == 0)) || ( (col == 0) || (row == 0)) ){
				// scaled pixels
			    out[x][y] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
				out[xb][y] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
			    out[x][yb] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
			    out[xb][yb] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;	

			} else if ((row%2 == 0) && (col%2 == 0)) {
				//scaled pixels
			    out[x][y] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
				out[xb][y] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
			    out[x][yb] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;
			    out[xb][yb] = (img[x][y] + img[x][yb] + img[xb][y] + img[xb][yb])/4;		
			}
		}
	}

	// and save this new image to file "outImage.pgm"
	writeImage(out, h, w);

}


// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	//int x;
	ifstream instr;
	instr.open("inImage.pgm");

	// read the header P2
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}
