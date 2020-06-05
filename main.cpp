/*
space to pause
Q to quit
S to save
L to load
H to display ammount of operations per second
U to turn on/off screen update. When turned off works much faster

Known issue: doesn't quit when paused
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "SDL.h"
using namespace std;



//got this function from https://sdl.beuc.net/sdl.wiki/Pixel_Access
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}



int main (int argc, char** argv)
{
  int x = 0, y = 0, step = 51, counter = 0, A = 0;   //recomended steps: 1(255 iterations per color); 3(85); 5(51); 15(17); 17(15); 51(5); 85(3); 255(1)
  bool stop = false, pause = false, update = true, how_fast = false;
  string filename;
  fstream f;

  cout << "X = ";
  cin >> x;
  cout << "Y = ";
  cin >> y;

  int xy = x * y;
  vector <int> r (xy, 0);
  vector <int> g (xy, 0);
  vector <int> b (xy, 0);

  Uint32 color = 0, begin_tick = 0;
  int how_fast_count = 0;
  SDL_Init (SDL_INIT_VIDEO);
  SDL_Event Event;
  SDL_KeyboardEvent KbrdEvent;
  SDL_Surface* Surface;
  SDL_Window* MainWindow = SDL_CreateWindow (
                                            "AllPics V3.1",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            x,
                                            y,
                                            0
                                            );
  begin_tick = SDL_GetTicks ();
  while (!stop)
  {
    if (how_fast && (SDL_GetTicks () - begin_tick) >= 1000)
    {
      cout << "Iterations per last second: " << how_fast_count << endl;
      begin_tick = SDL_GetTicks ();
      how_fast_count = 0;
    }
    if (how_fast && (SDL_GetTicks () - begin_tick) < 1000)
    {
      how_fast_count += 1;
    }

    pause_place:
    while (SDL_PollEvent (&Event))
    {
      KbrdEvent = Event.key;

      if (Event.type == SDL_QUIT || (KbrdEvent.keysym.scancode == SDL_SCANCODE_Q && KbrdEvent.type == SDL_KEYDOWN))
      {
        program_end:
        stop = true;
        cout << "Quitting... ";
      }

      if (KbrdEvent.type == SDL_KEYDOWN)
      {
        switch (KbrdEvent.keysym.scancode)
        {
          case SDL_SCANCODE_SPACE:
            pause = !pause;
            if (pause)
            {
              cout << "Paused." << endl;
            } else
            {
              cout << "Unpaused." << endl;
            }
            break;



//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//        SAVING
          case SDL_SCANCODE_S:
            cout << "Saving... " << endl;
            cout << "Enter save file name (no spaces allowed): ";
            cin >> filename;

            f.open (filename, ios::out);
            if (f.is_open ())
            {
              f << x << ' ' << y << ' ' << counter << endl;
              for (int i = 0; i < xy; i++)
              {
                f << r [i] << ' ';
              }

              f << endl;

              for (int i = 0; i < xy; i++)
              {
                f << g [i] << ' ';
              }

              f << endl;

              for (int i = 0; i < xy; i++)
              {
                f << b [i] << ' ';
              }
              cout << "Saved." << endl;
            } else
            {
              cout << "Error: couldn't open file." << endl;
            }
            f.close ();
            break;



//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//          LOADING
            case SDL_SCANCODE_L:
              cout << "Loading... " << endl;
              cout << "Enter save file name (no spaces allowed): ";
              cin >> filename;

              f.open (filename, ios::in);
              if (f.is_open ())
              {
                r.resize (0);
                g.resize (0);
                b.resize (0);
                SDL_DestroyWindow (MainWindow);
                f >> x;
                f >> y;
                xy = x * y;
                f >> counter;
                for (int i = 0; i < xy; i++)
                {
                  f >> A;
                  r.push_back (A);
                }

                for (int i = 0; i < xy; i++)
                {
                  f >> A;
                  g.push_back (A);
                }

                for (int i = 0; i < xy; i++)
                {
                  f >> A;
                  b.push_back (A);
                }
                MainWindow = SDL_CreateWindow (
                                                "AllPics V3.1",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                x,
                                                y,
                                                0
                                                );
                Surface = SDL_GetWindowSurface (MainWindow);
                SDL_LockSurface (Surface);
                for (int i = 0; i < xy; i++)
                {
                  color = SDL_MapRGB (Surface -> format, r[i], g[i], b[i]);
                  putpixel (Surface, (i % x), (i / x), color);
                }
                SDL_UnlockSurface (Surface);
                SDL_UpdateWindowSurface (MainWindow);
                pause = true;
                cout << "Loaded and paused." << endl;
              } else
              {
                cout << "Error: couldn't open file." << endl;
              }
              f.close ();
              break;



            case SDL_SCANCODE_U:
              update = !update;
              if (update)
              {
                cout << "Screen update enabled." << endl;
              } else
              {
                cout << "Screen update disabled." << endl;
              }
              break;



            case SDL_SCANCODE_H:
              how_fast = !how_fast;
              if (how_fast)
              {
                cout << "Delay counter enabled." << endl;
              } else
              {
                cout << "Delay counter disabled." << endl;
              }

        }
      }

    }

    if (pause)
    {
      goto pause_place;
    }



    if (counter >= xy && !stop)
    {
      cout << "Program finished." << endl;
      stop = true;
      goto program_end;
    } else
    {
      if (r[counter] >= 255)
      {
        r[counter] = 0;
        if (g[counter] >= 255)
        {
          g[counter] = 0;
          if (b[counter] >= 255)
          {
            b[counter] = 0;
            counter += 1;
          } else
          {
            b[counter] += step;
            counter = 0;
          }
        } else
        {
          g[counter] += step;
          counter = 0;
        }
      } else
      {
        r[counter] += step;
        counter = 0;
      }
    }

      Surface = SDL_GetWindowSurface (MainWindow);
      color = SDL_MapRGB (Surface->format, r[counter], g[counter], b[counter]);
      SDL_LockSurface (Surface);
      putpixel (Surface, (counter % x), (counter / x), color);
      SDL_UnlockSurface (Surface);
      if (update)
      {
        SDL_UpdateWindowSurface (MainWindow);
      }

    //cout << "Loop." << endl;
    //SDL_Delay (100);
  }


  r.resize (0);
  g.resize (0);
  b.resize (0);
  Uint32 worked_for = SDL_GetTicks ();
  SDL_DestroyWindow (MainWindow);
  SDL_Quit ();
  cout << "done." << endl;

  int days = 0, hours = 0, minutes = 0, seconds = 0;

  cout << "Program worked for";

  days = worked_for / 8640000;
  if (days)
  {
    cout << ' ' << days << 'd';
    worked_for /= 8640000;
  }

  hours = worked_for / 3600000;
  if (hours)
  {
    cout << ' ' << hours << 'h';
    worked_for /= 3600000;
  }

  minutes = worked_for / 60000;
  if (minutes)
  {
    cout << ' ' << minutes << 'm';
    worked_for /= 60000;
  }

  seconds = worked_for / 1000;
  if (seconds)
  {
    cout << ' ' << seconds << 's' << endl;
  } else
  {
    cout << endl;
  }
  return 0;
}
