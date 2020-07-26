#include <iostream>
#include <fstream>


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





bool file_exist (std::string path)
{
  std::fstream f;
  f.open (path, std::ios::in);
  if (f.is_open ())
  {
    f.close ();
    return true;
  }

  return false;
}





bool str_to_int (std::string s, int* x)
{
  *x = 0;
  for (int i = s.length () - 1; i >= 0; i--)
  {
    switch (s[i])
    {
      case '0':
      break;


      case '1':
      *x += pow (10, s.length () - 1 - i);
      break;


      case '2':
      *x += 2 * pow (10, s.length () - 1 - i);
      break;


      case '3':
      *x += 3 * pow (10, s.length () - 1 - i);
      break;


      case '4':
      *x += 4 * pow (10, s.length () - 1 - i);
      break;


      case '5':
      *x += 5 * pow (10, s.length () - 1 - i);
      break;


      case '6':
      *x += 6 * pow (10, s.length () - 1 - i);
      break;


      case '7':
      *x += 7 * pow (10, s.length () - 1 - i);
      break;


      case '8':
      *x += 8 * pow (10, s.length () - 1 - i);
      break;


      case '9':
      *x += 9 * pow (10, s.length () - 1 - i);
      break;


      case '-':
      if (!i)
      {
        *x *= -1;
      } else
      {
        *x = 0;
        return false;
      }
      break;


      default:
      return false;
      break;
    }
  }

  return true;
}





bool handle_events
(
  bool* stop,
  bool* pause,
  bool* s,
  bool* l,
  bool* update,
  bool* how_fast,
  bool* autosave,
  bool* autosave_overwrite,
  std::string* auto_path,
  std::string* filename,
  int* it_p_color,
  float* step
)
{

  int x = 0;
  SDL_Event Event;
  //SDL_KeyboardEvent KbrdEvent;
  std::string choise;

  while (SDL_PollEvent (&Event))
  {
    //KbrdEvent = Event.key;

    if (Event.type == SDL_QUIT || (Event.key.keysym.scancode == SDL_SCANCODE_Q && Event.key.type == SDL_KEYDOWN))
    {
      *stop = true;
      std::cout << "Quitting... ";
      return true;
    }


    if (Event.key.type == SDL_KEYDOWN)
    {
      switch (Event.key.keysym.scancode)
      {
        case SDL_SCANCODE_SPACE:
        *pause = !*pause;
        if (*pause)
        {
          std::cout << "Paused.\n";
        } else
        {
          std::cout << "Unpaused.\n";
        }
        break;




        case SDL_SCANCODE_S:
        std::cout << "Saving... \n"
        << "Enter save file name: ";
        getline (std::cin, *filename);

        if (file_exist (*filename))
        {
          std::cout << "File with this name already exist. Overwrite it ? (y/n) ";
          getline (std::cin, choise);
          if (tolower (choise[0]) == 'y')
          {
            *s = true;

          } else
          {
            std::cout << "Cancelled.\n";
          }

        } else
        {
          *s = true;
        }
        break;



        case SDL_SCANCODE_L:
          std::cout << "Loading... \n"
          << "Enter save file name: ";
          getline (std::cin, *filename);

          if (file_exist (*filename))
          {
            *l = true;

          } else
          {
            std::cout << "Couldn't open file. Cancelled.\n";
          }
          break;




        case SDL_SCANCODE_U:
          *update = !*update;
          if (*update)
          {
            std::cout << "Screen update enabled.\n";
          } else
          {
            std::cout << "Screen update disabled.\n";
          }
          break;




        case SDL_SCANCODE_H:
          *how_fast = !*how_fast;
          if (*how_fast)
          {
            std::cout << "Delay counter enabled.\n";
          } else
          {
            std::cout << "Delay counter disabled.\n";
          }
          break;




        case SDL_SCANCODE_A:
          std::cout << "Iterations per color (min: 1; max: 255): ";
          getline (std::cin, choise);


          if (str_to_int (choise, &x))
          {
            //

          if (x > 255)
          {
            std::cout << "Entered number is greater than 255. It will be set to 255.\n";
            x = 255;
          }

          if (x < 1)
          {
            std::cout << "Entered number is less than 1. It will be set to 1.\n";
            x = 1;
          }
          *it_p_color = x;
          *step = 255.0 / (*it_p_color * 1.0);
          } else
          {
            std::cout << "Error detecting number. Cancelled.\n";
          }
          break;




        case SDL_SCANCODE_C:
          *autosave = !*autosave;
          if (*autosave)
          {
            if (file_exist (*auto_path) && !*autosave_overwrite)
            {
              std::cout << "File \"" << *auto_path << "\" already exist. Overwrite it (y/n)? ";
              getline (std::cin, choise);
              if (tolower (choise[0]) == 'y')
              {
                *autosave_overwrite = true;

              } else
              {
                *autosave = false;
                std::cout << "Autosave is not enabled.\n";
              }
            } else
            {
              *autosave_overwrite = true;
              std::cout << "Autosave enabled.\n";
            }
          } else
          {
            std::cout << "Autosave disabled.\n";
          }
      }
    }

  }

  return false;
}




void help (const char* launched)
{
  std::cout
  << "AllPics is a relatively simple SDL-based program (http://libsdl.com) program to generate images. Works slowly, but works.\n\n"

  << launched << " [arguments]\n"
  << "Possible arguments:\n"
  << "    --help (-h)                     ‒ print help and exit;\n"
  << "    --load FILE (-l FILE)           ‒ load data from FILE;\n"
  << "    --autosave (-a)                 ‒ autosave enabled by default;\n"
  << "    --autosavef FILE (-A FILE)      ‒ changes autosave file to FILE, default - \"AllPics.AUTOSAVE\";\n\n"

  << "When launched:\n"
  << "    SPACE       ‒ pause/unpause;\n"
  << "    Q           ‒ quit;\n"
  << "    S           ‒ save;\n"
  << "    L           ‒ load;\n"
  << "    H           ‒ display ammount of operations per second, default ‒ off;\n"
  << "    U           ‒ turn on/off screen update. When turned off works much faster, default ‒ on;\n"
  << "    A           ‒ adjust iterations per color.\n"
  << "    C           ‒ enable/disable autosave, default ‒ off;\n\n"
  ;
}
