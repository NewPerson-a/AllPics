ABOUT
AllPics is a simple SDL-based (https://libsdl.org/) program that can show you every image possible if given enough time. The problem is it requires a lot of time. Still, it works. When you start the application it asks you for width and height of the window, and for amount of steps per color. Once you entered this data it creates a window and starts changing pixels.

HOW TO USE
Possible command line/terminal arguments:
    --help (-h)                     ‒ print help and exit;
    --load FILE (-l FILE)           ‒ load data from FILE;
    --autosave (-a)                 ‒ autosave enabled by default;
    --autosavef FILE (-A FILE)      ‒ changes autosave file to FILE, default - "AllPics.AUTOSAVE";

When launched:
    SPACE       ‒ pause/unpause;
    Q           ‒ quit;
    S           ‒ save;
    L           ‒ load;
    H           ‒ display ammount of operations per second, default ‒ off;
    U           ‒ turn on/off screen update. When turned off works much faster, default ‒ on;
    A           ‒ adjust iterations per color.
    C           ‒ enable/disable autosave, default ‒ off;


Note: you will need a terminal or a console to run this application. This will be changed in future.
Second note: this program should work under any desktop platform, but was only tested under debian linux.
Third note: version 3.3 has different file save format than 3.4 (which is current). If someone really found this program and uses it, code in "convertSave_3.3_to_3.4.cpp" converts old save file so that it can be used with new version.

ALGORITHM
Each pixel consists of five variables: x-position, y-position, red, green, blue. At first we increase the red value a bit. Once it reaches 255 we set it back to zero and increase the green value. Once green reaches 255, we set it to 0 and increase blue value. And when it reaches 255, we set it to 0 and increase the red value of the next pixel. And so on. The program finishes when the number of next pixel is more than amount of pixels.



Also, I've found out that there are some things called AllPics in the Internet. Didn't try to figure what those are, but just in case: I have no relation to anything beyond this github profile.
