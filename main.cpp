#include "CImg.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace cimg_library;

typedef struct pixel{
	int greyVal;
	int rgb[3];
}pixel;

//Comparator
bool cmp_lum(const pixel &a, const pixel &b){
	return (a.greyVal < b.greyVal);
}

//Prototype declaration
void sortPixels(std::vector<pixel> &segment, CImg<unsigned char> &img_sort, int o_ind, int start, bool vert);

//Main is for everything. this is proper coding conduct
int main(int argc, char **argv){
	
	//--------------------CImg cli arguments------------------------
	cimg_usage("Get arguments");
	const char* fname = cimg_option("-i", "input/moss.jpg", "input image file");
	const int thresh_l = cimg_option("-l", 30, "lower threshold boundary");
	const int thresh_u = cimg_option("-u", 210, "upper threshold boundary");
	const bool vert = cimg_option("-v", true, "sorting direction");
	const char* output = cimg_option("-o", (char*)0, "output image file");

	//Construct input img, a copy, and space for grey img
	CImg<unsigned char> img(fname),
		img_sort(img),
		img_grey(img.width(), img.height(), 1, 1, 0);

	//o_ and i_ represent outer and inner loop respectively
	//Default loop is column->row(XY) for vertical sort	
	int o_max, i_max, o_ind, i_ind;
	o_max = img.width();
	i_max = img.height();	
	//x and y pointers to generalize looping direction(i.e. XY vs YX)
	int *x = &o_ind;
	int *y = &i_ind;
	if(!vert){
		o_max = img.height();
		i_max = img.width();
		x = &i_ind;
		y = &o_ind;
	}

	//Vector to hold relevant pixels
	std::vector<pixel> segment;
	
	//Begin looping through array
	for (o_ind = 0; o_ind < o_max; o_ind++){
		int counter = 0;
		int start;
		for(i_ind = 0; i_ind < i_max; i_ind++){
			int R = (int)img(*x, *y, 0);
			int G = (int)img(*x, *y, 1);
			int B = (int)img(*x, *y, 2);
			//Weighted by sensitivity to light (?? I copied it from somewhere)
			int grey = (int)(0.299*R + 0.587*G + 0.114*B);
			
			//Threshold grey intensity
			if ((grey < thresh_l) || (grey > thresh_u))
			{
				if(counter > 1) sortPixels(segment, img_sort, o_ind, start, vert);
				grey = 0;
				counter = 0;
			}else{
				if(counter == 0) start = i_ind;
				pixel newPix = {grey, {R, G, B}};
				segment.push_back(newPix);
				counter++;
			}
			//Included to visualize the roi
			img_grey(*x, *y, 0) = grey;
		}
		//Sort & update if segment extends to image border
		if (!segment.empty()) sortPixels(segment, img_sort, o_ind, start, vert);
	}

	//Set up display windows and draw images
	CImgDisplay window(img, "Original"), 
		    draw_winGrey(img_grey, "Grey"),
		    draw_winSort(img_sort, "Sorted");

	while(!window.is_closed()) window.wait();

	//Write pixelsorted img
	if(output) img_sort.save(output);

	return 0;
}

//Declaration of sortPixels
//Sorts and updates image
void sortPixels(std::vector<pixel> &segment, CImg<unsigned char> &img_sort, int o_ind, int start, bool vert){
	//Sort
	std::sort(segment.begin(), segment.end(), cmp_lum);
 	
	//ptrs to help generalize loop direction
	int ind = start;		
	int *x, *y;
        x = &o_ind;
	y = &ind;
	if(!vert){
		y = &o_ind;
		x = &ind;
	}

	//Update
	for (int i = 0; i < segment.size(); i++, ind++)
	{
		img_sort(*x, *y, 0) = segment[i].rgb[0];
		img_sort(*x, *y, 1) = segment[i].rgb[1];
		img_sort(*x, *y, 2) = segment[i].rgb[2];
	}
	segment.clear();
}
