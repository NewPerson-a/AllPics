ABOUT
AllPics is a simple SDL-based program that can show you every image possible if given enough time. The problem is it requires a lot of time. Still, it works. When you start the aplication it asks you for width and height of the window. Once you entered it creates a window and starts to change pixels.

HOW TO USE
SPACE ‒ pause/unpace; 
S ‒ save;
L - load;
U - turn on/off window update. Works much fuster when turned off;
H - turn on/of display of ammount of pixel changes per second
Q - quit

Note: you will need a terminal or console to run this application. This will be changed in future.
Second note: this program should work under any desktop platform, but was only tested under debian linux

ALGORITM
Each pixel consists of five variables: x-position, y-position, red, green, blue. At first we increase the red value a bit. Once it reaches 255 we set it back to zero and increase the green value. Once green reaches 255, we set it to 0 and increase blue value. And when it reaches 255, we set it to 0 and increase the red value of the next pixel. And so on. The program finishes when the number of next pixel is more than amount of pixels.
