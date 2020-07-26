#include <cstdlib>
#include <iostream>
#include <fstream>
#include "convert.h"


bool file_exist (const char* path)
{
  std::filebuf f;
  f.open (path, std::ios::in);

  if (f.is_open ())
  {
    f.close ();
    return true;
  }

  return false;
}





int main (int argc, char** argv)
{
  if (argc < 3)
  {
    std::cout
    << "This program was created to convert old save files to new format.\n"
    << "Usage: " << argv[0] << " old_save_filename new_save_filename\n";
    return -1;
  }

  std::fstream old_f;
  std::filebuf new_f;


  std::string inp;

  if (file_exist (argv[2]))
  {
    std::cout << "File \"" << argv[2] << "\" already exist. Overwrite it? (y/n) ";
    getline (std::cin, inp);
    if (tolower (inp[0]) != 'y')
    {
      std::cout << "Abort.\n";
    }
  }


  old_f.open (argv[1], std::ios::in);
  if (!old_f.is_open ())
  {
    std::cout << "Failed to open \"" << argv[1] << "\". Abort\n";
    return -1;
  }



  new_f.open (argv[2], std::ios::out | std::ios::binary);
  if (!new_f.is_open ())
  {
    std::cout << "Failed to open \"" << argv[2] << "\". Abort\n";
    return -1;
  }




  std::cout << "Converting... ";
  fflush (stdout);


  //int f_size = old_f.rdbuf ()->in_avail ();
  int x = 0, y = 0, xy = 0, counter = 0, it_p_color = 0;

  float read_float = 0.0, *data = NULL;
  unsigned char* div_int = NULL;

  old_f >> x;
  old_f >> y;
  old_f >> counter;

  xy = x * y;




  data = (float*) calloc (xy * 3, sizeof (float));
  div_int = (unsigned char*) calloc (4, 1);

  if (data == NULL || div_int == NULL)
  {
    std::cout << "Memory allocation error. Abort.\n";
    old_f.close ();
    new_f.close ();
    return -1;

  }



  for (int i = 0; i < xy; i++)
  {
    old_f >> read_float;
    data[i] = read_float;
  }


  old_f >> it_p_color;
  old_f.close ();


  if (it_p_color < 1)
  {
    it_p_color = 1;
  }


  if (it_p_color > 255)
  {
    it_p_color = 255;
  }

  const short int sign[256] = {65, 194, 112, 175, 214, 105, 243, 128, 44, 40, 211, 102, 72, 178, 247, 222, 120, 189, 53, 173, 37, 72, 77, 20, 21, 179, 132, 87, 245, 206, 234, 55, 144, 90, 230, 102, 196, 218, 231, 240, 2, 186, 86, 74, 108, 77, 41, 229, 10, 94, 146, 47, 166, 223, 68, 188, 146, 200, 19, 135, 150, 253, 190, 38, 88, 165, 141, 28, 127, 116, 12, 129, 46, 99, 204, 155, 176, 245, 128, 187, 83, 18, 234, 250, 241, 46, 182, 131, 246, 201, 10, 140, 198, 201, 179, 30, 110, 64, 58, 237, 180, 71, 110, 226, 170, 58, 125, 90, 47, 253, 21, 131, 15, 0, 125, 0, 46, 51, 131, 37, 252, 142, 177, 194, 87, 100, 225, 197, 164, 27, 178, 88, 98, 32, 59, 12, 91, 184, 103, 138, 182, 124, 13, 197, 124, 138, 198, 171, 189, 73, 208, 185, 215, 129, 124, 46, 230, 93, 243, 138, 120, 165, 227, 219, 198, 30, 231, 33, 214, 78, 171, 140, 203, 185, 82, 71, 67, 24, 242, 1, 97, 194, 186, 57, 68, 54, 103, 42, 147, 91, 180, 12, 0, 151, 231, 198, 181, 206, 231, 140, 29, 147, 24, 232, 76, 106, 47, 143, 130, 34, 144, 228, 228, 75, 29, 40, 129, 132, 82, 21, 223, 7, 33, 224, 158, 8, 166, 84, 214, 142, 224, 243, 33, 248, 219, 109, 99, 11, 252, 229, 45, 141, 201, 17, 216, 230, 58, 89, 107, 140, 110, 74, 147, 143, 42, 50};


  for (int i = 0; i < 256; i++)
  {
    new_f.sputc (sign[i]);
  }


  convert_int_to_chars (276 + (xy * 3), div_int);
  new_f.sputc (div_int[0]);
  new_f.sputc (div_int[1]);
  new_f.sputc (div_int[2]);
  new_f.sputc (div_int[3]);


  convert_int_to_chars (x, div_int);
  new_f.sputc (div_int[0]);
  new_f.sputc (div_int[1]);
  new_f.sputc (div_int[2]);
  new_f.sputc (div_int[3]);


  convert_int_to_chars (y, div_int);
  new_f.sputc (div_int[0]);
  new_f.sputc (div_int[1]);
  new_f.sputc (div_int[2]);
  new_f.sputc (div_int[3]);


  convert_int_to_chars (counter, div_int);
  new_f.sputc (div_int[0]);
  new_f.sputc (div_int[1]);
  new_f.sputc (div_int[2]);
  new_f.sputc (div_int[3]);


  convert_int_to_chars (it_p_color, div_int);
  new_f.sputc (div_int[0]);
  new_f.sputc (div_int[1]);
  new_f.sputc (div_int[2]);
  new_f.sputc (div_int[3]);


  xy *= 3;

  for (int i = 0; i < xy; i++)
  {
    new_f.sputc (data[i]);
  }


  new_f.close ();

  free (data);
  free (div_int);
  std::cout << "Succsess.\n";
  return 0;
}
