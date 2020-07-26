#include "SDL.h"
#include "args.h"
#include "save_load.h"



int main (int argc, char** argv)
{
  int x = 0, y = 0, xy = 0,
  counter = 0, it_p_color = 0, how_fast_count = 0, autosave_counter = 0;

  bool stop = false, pause = false, update = true, how_fast = false,
  autosave = false, autosave_overwrite = false, mlock = false,
  s = false, l = false;

  float step = 0.0, *r = NULL, *g = NULL, *b = NULL;

  std::string auto_path = "AllPics.AUTOSAVE", filename, choise;



  if (argc > 1)
  {
    if (get_t_input (argc, argv, &filename, &l, &autosave, &auto_path))
    {
      return 0;
    }


  }

  char* ch = new char ('\0');

  if (l)
  {
    l = false;
    std::cout << "Loading...\n";
    *ch = load
    (
      filename.c_str (),
      &x,
      &y,
      &xy,
      &counter,
      &it_p_color,
      &step,
      &r,
      &g,
      &b
    );

    switch (*ch)
    {
      case 'r':
        std::cout << "This is not an AllPics save file or it is corrupted.\n";
        break;


      case 's':
        std::cout << "File is corrupted.\n";
        break;


      case 'f':
        std::cout << "Couldn't open file.\n";
        break;


      case 'n':        std::cout << "Loading succsessful\n";
        break;
    }

  }


  if (*ch != 'n')
  {
    do
    {
      std::cout << "X = ";
      getline (std::cin, choise);

    } while (!str_to_int (choise, &x));


    do
    {
      std::cout << "Y = ";
      getline (std::cin, choise);

    } while (!str_to_int (choise, &y));

    xy = x * y;


    std::cout << "\nThe higher this number is the higer quality of the image and the slower its generation;\n";

    do
    {
      std::cout << "Iterations per color (min: 1; max: 255): ";
      getline (std::cin, choise);

    } while (!str_to_int (choise, &it_p_color));

    if (it_p_color > 255)
    {
      std::cout << "Entered number is greater than 255. It will be set to 255.\n";
      it_p_color = 255;
    }

    if (it_p_color < 1)
    {
      std::cout << "Entered number is less than 1. It will be set to 1.\n";
      it_p_color = 1;
    }
    step = 255.0 / it_p_color;



    r = (float*) calloc (xy, sizeof (float));
    g = (float*) calloc (xy, sizeof (float));
    b = (float*) calloc (xy, sizeof (float));

  }


  Uint32 color = 0, begin_tick = 0, autosave_tick = 0;
  SDL_Init (SDL_INIT_VIDEO);

  SDL_Window* MainWindow =
  SDL_CreateWindow
  (
    "AllPics V3.4",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    x,
    y,
    0
  );
  SDL_Surface* Surface = SDL_GetWindowSurface (MainWindow);
  mlock = SDL_MUSTLOCK (Surface);


  if (*ch == 'n')
  {
    if (mlock)
    {
      SDL_LockSurface (Surface);
    }


    for (int i = 0; i < xy; i++)
    {
      color = SDL_MapRGB (Surface->format, (int) r[i], (int) g[i], (int) b[i]);
      putpixel (Surface, (i % x), (i / x), color);
    }


    if (mlock)
    {
      SDL_UnlockSurface (Surface);
    }
  }

  delete ch;
  begin_tick = SDL_GetTicks ();




  while (!stop)
  {
    handle_events
    (
      &stop,
      &pause,
      &s,
      &l,
      &update,
      &how_fast,
      &autosave,
      &autosave_overwrite,
      &auto_path,
      &filename,
      &it_p_color,
      &step
    );


    if (l)
    {
      l = false;


      std::cout << "Loading... ";
      fflush (stdout);

      char check = load
      (
        filename.c_str (),
        &x,
        &y,
        &xy,
        &counter,
        &it_p_color,
        &step,
        &r,
        &g,
        &b
      );


      switch (check)
      {
        case 'r':
          std::cout << "This is not an AllPics save file or it is corrupted.\n";
          break;


        case 's':
          std::cout << "File is corrupted.\n";
          break;


        case 'f':
          std::cout << "Couldn't open file.\n";
          break;


        case 'a':
          std::cout << "Reallocation error. Possible reason: insufficient RAM.\nThis error is critical. Exiting... ";
          stop = true;
          free (r);
          free (g);
          free (b);
          break;


        case 'n':


          SDL_DestroyWindow (MainWindow);


          MainWindow =
          SDL_CreateWindow
          (
            "AllPics V3.4",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            x,
            y,
            0
          );



          if (MainWindow == NULL)
          {
            std::cout << "Critical error while creating window: " << SDL_GetError () << " Exiting... ";
            return 0;
          }


          Surface = SDL_GetWindowSurface (MainWindow);
          if (Surface == NULL)
          {
            std::cout << "Critical error while getting window surface: " << SDL_GetError () << " Exiting... ";
            return 0;
          }



          mlock = SDL_MUSTLOCK (Surface);

          if (mlock)
          {
            SDL_LockSurface (Surface);
          }


          for (int i = 0; i < xy; i++)
          {
            color = SDL_MapRGB (Surface->format, (int) r[i], (int) g[i], (int) b[i]);
            putpixel (Surface, (i % x), (i / x), color);
          }


          if (mlock)
          {
            SDL_UnlockSurface (Surface);
          }

          SDL_UpdateWindowSurface (MainWindow);
          pause = true;
          std::cout << "Loading succsessful. Program paused.\n";
          break;
      }

      //std::cout << "done.\n";
    }





    if (s)
    {
      s = false;
      std::cout << "Saving... ";
      fflush (stdout);

      switch
      (
        save
        (
          filename.c_str (),
          x,
          y,
          xy,
          counter,
          it_p_color,
          r,
          g,
          b
        )
      )
      {
        case 'f':
          std::cout << "Error: couldn't open file.\n";
          break;


        case 'n':
          std::cout << "done.\n";
          break;
      }
    }




    if (pause)
    {
      SDL_Delay (100);

    } else
    {


      if (how_fast && !stop)
      {
        if (SDL_GetTicks () - begin_tick >= 1000)
        {
          std::cout << "Iterations per last second: " << how_fast_count << std::endl;
          //fflush (stdout);
          begin_tick = SDL_GetTicks ();
          how_fast_count = 0;

        } else
        {
          how_fast_count += 1;
        }
      }



      if (autosave && !stop)
      {
        if ((SDL_GetTicks () - autosave_tick) >= 60000)
        {
          std::cout << "Autosaving... ";
          fflush (stdout);

          switch
          (
            save
            (
              auto_path.c_str (),
              x,
              y,
              xy,
              counter,
              it_p_color,
              r,
              g,
              b
            )
          )
          {
            case 'f':
              std::cout << "Error: couldn't open autosave file.\n";
              break;


            case 'n':
              std::cout << "done.\n";
              break;
          }
          autosave_tick = SDL_GetTicks ();
        }
      }


      if (counter >= xy && !stop)
      {
        std::cout << "Program finished.\n";
        stop = true;

      } else
      {
        if (r[counter] >= 255.0)
        {
          r[counter] = 0.0;
          if (g[counter] >= 255.0)
          {
            g[counter] = 0.0;
            if (b[counter] >= 255.0)
            {
              b[counter] = 0.0;
              counter += 1;
            } else
            {
              b[counter] += step;
              counter = 0.0;
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


        if (mlock)
        {
          SDL_LockSurface (Surface);
        }

        color = SDL_MapRGB (Surface->format, r[counter], g[counter], b[counter]);
        putpixel (Surface, (counter % x), (counter / x), color);

        if (mlock)
        {
          SDL_UnlockSurface (Surface);
        }


        if (update)
        {
          SDL_UpdateWindowSurface (MainWindow);
        }
      }

    }
  }
//end of while (!stop)





  free (r);
  free (g);
  free (b);


  Uint32 worked_for = SDL_GetTicks ();

  SDL_DestroyWindow (MainWindow);
  SDL_Quit ();



  std::cout << "done.\n";

  Uint32 days = 0, hours = 0, minutes = 0, seconds = 0;

  std::cout << "Program worked for";


  seconds = worked_for / 1000;
  if (seconds > 59)
  {
    minutes = seconds / 60;
    seconds %= 60;
  }

  if (minutes > 59)
  {
    hours = minutes / 60;
    minutes %= 60;
  }

  if (hours > 23)
  {
    days = hours / 24;
    hours %= 24;
  }


  if (days)
  {
    std::cout << ' ' << days << 'd';
  }
  if (hours)
  {
    std::cout << ' ' << hours << 'h';
  }
  if (minutes)
  {
    std::cout << ' ' << minutes << 'm';
  }
  std::cout << ' ' << seconds << "s\n";
  return 0;
}
