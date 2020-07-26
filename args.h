#include <vector>
#include "misc.h"

//returns true if --help or -h passed
bool get_t_input
(
  int argc,
  char** argv,
  std::string* load_path,
  bool* l,
  bool* autosave,
  std::string* auto_path
)
{
  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i], s, choise;

    if (arg.substr (0, 2) == "--")
    {
      arg = arg.substr (2, arg.length ());
      bool unknown = true;



      if (arg == "load")
      {
        if (i + 1 < argc) //if there is something after "load"
        {
          *l = true;
          *load_path = argv[++i];
        } else
        {
          std::cout << "Error at argument #" << i << " (" << arg << "): no file path provided.\n";
        }

        unknown = false;
      }



      if (arg == "autosavef")
      {
        if (i + 1 < argc) //if there is something after "autosave"
        {
          *auto_path = argv[++i];

        } else
        {
          std::cout << "Error at argument #" << i << " (" << arg << "): no file path provided.\n";
        }
        unknown = false;
      }



      if (arg == "autosave")
      {
        *autosave = true;
        unknown = false;
      }



      if (arg == "help")
      {
        help (argv[0]);
        return true;
      }



      if (unknown)
      {
        std::cout << "Error at argument #" << i << " (" << arg << "): unknown argument.\n";
      }


    } else
    {
      if (arg[0] == '-')
      {
        s = arg.substr (1, arg.length ());

        for (int j = 0; j < s.length (); j++)
        {
          switch (s[j])
          {
            case 'l':
              if (i + 1 < argc) //if there is something after "load"
              {
                *l = true;
                *load_path = argv[++i];
              } else
              {
                std::cout << "Error at argument #" << i << " (" << s[j] << "): no file path provided.\n";
              }
              break;



            case 'a':
            {
              *autosave = true;
            }



            case 'A':
              if (i + 1 < argc) //if there is something after "autosave"
              {
                *auto_path = argv[++i];

              } else
              {
                std::cout << "Error at argument #" << i << " (" << s[j] << "): no file path provided.\n";
              }
            break;



            case 'h':
              help (argv[0]);
              return true;
              break;



            default:
              std::cout << "Error at argument #" << i << " (" << s[j] << "): Unknown argument\n";
              break;
          }
        }

      }
    }

  }
  return false;
}
