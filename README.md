# PixelSort CLI
A CImg based implementation of pixel sorting--a technique popularized by visual artist [Kim Asendorf](http://kimasendorf.com/) whose github can be found [here](https://github.com/kimasendorf).

Really dig how simple the idea is + cool the results are:
  1. Apply a binary threshold to create pixel segments along rows or columns (this helps retain features of the original image)
  2. Sort the segments by some measurable metric (in this case, I used luminance--could also use hue, saturation, etc.)

The program displays the sorted, greyscale, and original images before exiting.  

## Example
```
./pixelsort -i input/moss.jpg -o output/moss_v.jpg -l 30 -u 210 -v true
```  
<div align="center">
  <img width="400px" src="https://github.com/patwheeler/PixelSort/blob/main/input/moss.jpg?raw=true">
  <img width="400px" src="https://github.com/patwheeler/PixelSort/blob/main/output/moss_v.jpg?raw=true">
</div>

#### Usage
Options to sort pixels by column or row, tweak the threshold values(0-255), and save the pic.
```
-i (input image: default moss picture included in input/)
-o (output image: default no save)
-l (lower threshold: default 30)
-u (upper threshold: default 210)
-v (vertical: default true)
```

## Building on Linux
Compile using g++ and included makefile. i.e.```make```  

**Notes**: 
- *Requires ImageMagick for imports*
- *Occasional segfault when closing CImgDisplay windows*



