ABOUT
AllPics is a simple SDL-based (https://libsdl.org/) program that can show you every image possible if given enough time. The problem is it requires a lot of time. Still, it works. When you start the application it asks you for width and height of the window, and for amount of steps per color. Once you entered this data it creates a window and starts changing pixels.

HOW TO USE
SPACE ‒ pause/unpause;
Q ‒ quit;
S ‒ save;
L ‒ load;
H ‒ turn on/of display of amount of pixel changes per second, default ‒ off;
U ‒ turn on/off window update. Works much faster when turned off. Actually it is recommended to keep it off most of time and turn on only if you want to see current progress, default ‒ on;
A ‒ adjust amount of steps per color. The higher this number is the more detailed image can be generated and the slower program works;
C ‒ turn on/off autosave, default ‒ off;


Note: you will need a terminal or a console to run this application. This will be changed in future.
Second note: this program should work under any desktop platform, but was only tested under debian linux.
Yet another note: for some reason the program doesn't quit when paused, no matter how you try (even "sudo kill" didn't work), but it remembers that you wanted to quit and does so once unpaused.

ALGORITHM
Each pixel consists of five variables: x-position, y-position, red, green, blue. At first we increase the red value a bit. Once it reaches 255 we set it back to zero and increase the green value. Once green reaches 255, we set it to 0 and increase blue value. And when it reaches 255, we set it to 0 and increase the red value of the next pixel. And so on. The program finishes when the number of next pixel is more than amount of pixels.
