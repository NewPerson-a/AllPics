#include <fstream>
#include "convert.h"


char save
(
  const char* filename,
  int x,
  int y,
  int xy,
  int counter,
  int it_p_color,
  float* r,
  float* g,
  float* b
)
{
  std::filebuf f;
  f.open (filename, std::ios::out | std::ios::binary);
  if (f.is_open ())
  {

//  This string was randomly generated and is used to recognize save files
/*
    const char* sign = "\65\194\112\175\214\105\243\128\44\40\211\102\72\178\247\222\120\189\53\173\37\72\77\20\21\179\132\87\245\206\234\55\144\90\230\102\196\218\231\240\2\186\86\74\108\77\41\229\10\94\146\47\166\223\68\188\146\200\19\135\150\253\190\38\88\165\141\28\127\116\12\129\46\99\204\155\176\245\128\187\83\18\234\250\241\46\182\131\246\201\10\140\198\201\179\30\110\64\58\237\180\71\110\226\170\58\125\90\47\253\21\131\15\0\125\0\46\51\131\37\252\142\177\194\87\100\225\197\164\27\178\88\98\32\59\12\91\184\103\138\182\124\13\197\124\138\198\171\189\73\208\185\215\129\124\46\230\93\243\138\120\165\227\219\198\30\231\33\214\78\171\140\203\185\82\71\67\24\242\1\97\194\186\57\68\54\103\42\147\91\180\12\0\151\231\198\181\206\231\140\29\147\24\232\76\106\47\143\130\34\144\228\228\75\29\40\129\132\82\21\223\7\33\224\158\8\166\84\214\142\224\243\33\248\219\109\99\11\252\229\45\141\201\17\216\230\58\89\107\140\110\74\147\143\42\50";

    when done like that compiler doesn't like that there are 'unknown escape sequence'. It still compiles and works as intended, but makes it harder to see other compilation errors, so chars were replaced with short ints
*/


    const short int sign[256] = {65, 194, 112, 175, 214, 105, 243, 128, 44, 40, 211, 102, 72, 178, 247, 222, 120, 189, 53, 173, 37, 72, 77, 20, 21, 179, 132, 87, 245, 206, 234, 55, 144, 90, 230, 102, 196, 218, 231, 240, 2, 186, 86, 74, 108, 77, 41, 229, 10, 94, 146, 47, 166, 223, 68, 188, 146, 200, 19, 135, 150, 253, 190, 38, 88, 165, 141, 28, 127, 116, 12, 129, 46, 99, 204, 155, 176, 245, 128, 187, 83, 18, 234, 250, 241, 46, 182, 131, 246, 201, 10, 140, 198, 201, 179, 30, 110, 64, 58, 237, 180, 71, 110, 226, 170, 58, 125, 90, 47, 253, 21, 131, 15, 0, 125, 0, 46, 51, 131, 37, 252, 142, 177, 194, 87, 100, 225, 197, 164, 27, 178, 88, 98, 32, 59, 12, 91, 184, 103, 138, 182, 124, 13, 197, 124, 138, 198, 171, 189, 73, 208, 185, 215, 129, 124, 46, 230, 93, 243, 138, 120, 165, 227, 219, 198, 30, 231, 33, 214, 78, 171, 140, 203, 185, 82, 71, 67, 24, 242, 1, 97, 194, 186, 57, 68, 54, 103, 42, 147, 91, 180, 12, 0, 151, 231, 198, 181, 206, 231, 140, 29, 147, 24, 232, 76, 106, 47, 143, 130, 34, 144, 228, 228, 75, 29, 40, 129, 132, 82, 21, 223, 7, 33, 224, 158, 8, 166, 84, 214, 142, 224, 243, 33, 248, 219, 109, 99, 11, 252, 229, 45, 141, 201, 17, 216, 230, 58, 89, 107, 140, 110, 74, 147, 143, 42, 50};

    unsigned char ch = 0, *div_int = NULL;
    div_int = (unsigned char*) calloc (4, 1);

    if (div_int == NULL)
    {
      return 'a';                 //allocation error
    }



    for (int i = 0; i < 256; i++)
    {
      f.sputc (sign[i]);        //string for recognizion
    }


    unsigned int size =       //expected file size
    256 +       //recognizion string
    20 +        //expected size, x-resolution, y-resolution, counter, it_p_color (each 4 bytes)
    (xy * 3);   //xy pixels, each contains three colors, since they never exceed 255 one byte per each is just enough


    convert_int_to_chars (size, div_int);
    for (int i = 0; i < 4; i++)
    {
      f.sputc (div_int[i]);
    }


    convert_int_to_chars (x, div_int);
    for (int i = 0; i < 4; i++)
    {
      f.sputc (div_int[i]);
    }


    convert_int_to_chars (y, div_int);
    for (int i = 0; i < 4; i++)
    {
      f.sputc (div_int[i]);
    }


    convert_int_to_chars (counter, div_int);
    for (int i = 0; i < 4; i++)
    {
      f.sputc (div_int[i]);
    }


    convert_int_to_chars (it_p_color, div_int);
    for (int i = 0; i < 4; i++)
    {
      f.sputc (div_int[i]);
    }


    for (int i = 0; i < xy; i++)
    {
      ch = r[i];
      f.sputc (ch);
    }


    for (int i = 0; i < xy; i++)
    {
      ch = g[i];
      f.sputc (ch);
    }


    for (int i = 0; i < xy; i++)
    {
      ch = b[i];
      f.sputc (ch);
    }


    free (div_int);

  } else
  {
    return 'f'; //couldn't open file
  }

  f.close ();
  return 'n';   //normal
}





char load
(
  const char* filename,
  int* x,
  int* y,
  int* xy,
  int* counter,
  int* it_p_color,
  float* step,
  float** r,
  float** g,
  float** b
)//Yep. A pointer to a pointer to a float. Reason: during loading memory reallocation happens, and it is required to have new address beyond this function, otherwise segmentation fault is very likely
{
  std::filebuf f;
  f.open (filename, std::ios::in | std::ios::binary);
  if (f.is_open ())
  {

//  This string was randomly generated and is used to recognize save files
/*
    const char* sign = "\65\194\112\175\214\105\243\128\44\40\211\102\72\178\247\222\120\189\53\173\37\72\77\20\21\179\132\87\245\206\234\55\144\90\230\102\196\218\231\240\2\186\86\74\108\77\41\229\10\94\146\47\166\223\68\188\146\200\19\135\150\253\190\38\88\165\141\28\127\116\12\129\46\99\204\155\176\245\128\187\83\18\234\250\241\46\182\131\246\201\10\140\198\201\179\30\110\64\58\237\180\71\110\226\170\58\125\90\47\253\21\131\15\0\125\0\46\51\131\37\252\142\177\194\87\100\225\197\164\27\178\88\98\32\59\12\91\184\103\138\182\124\13\197\124\138\198\171\189\73\208\185\215\129\124\46\230\93\243\138\120\165\227\219\198\30\231\33\214\78\171\140\203\185\82\71\67\24\242\1\97\194\186\57\68\54\103\42\147\91\180\12\0\151\231\198\181\206\231\140\29\147\24\232\76\106\47\143\130\34\144\228\228\75\29\40\129\132\82\21\223\7\33\224\158\8\166\84\214\142\224\243\33\248\219\109\99\11\252\229\45\141\201\17\216\230\58\89\107\140\110\74\147\143\42\50";

    when done like that compiler doesn't like that there are 'unknown escape sequence'. It still compiles and works as intended, but makes it harder to see other compilation errors, so chars were replaced with short ints
*/

    const short int sign[256] = {65, 194, 112, 175, 214, 105, 243, 128, 44, 40, 211, 102, 72, 178, 247, 222, 120, 189, 53, 173, 37, 72, 77, 20, 21, 179, 132, 87, 245, 206, 234, 55, 144, 90, 230, 102, 196, 218, 231, 240, 2, 186, 86, 74, 108, 77, 41, 229, 10, 94, 146, 47, 166, 223, 68, 188, 146, 200, 19, 135, 150, 253, 190, 38, 88, 165, 141, 28, 127, 116, 12, 129, 46, 99, 204, 155, 176, 245, 128, 187, 83, 18, 234, 250, 241, 46, 182, 131, 246, 201, 10, 140, 198, 201, 179, 30, 110, 64, 58, 237, 180, 71, 110, 226, 170, 58, 125, 90, 47, 253, 21, 131, 15, 0, 125, 0, 46, 51, 131, 37, 252, 142, 177, 194, 87, 100, 225, 197, 164, 27, 178, 88, 98, 32, 59, 12, 91, 184, 103, 138, 182, 124, 13, 197, 124, 138, 198, 171, 189, 73, 208, 185, 215, 129, 124, 46, 230, 93, 243, 138, 120, 165, 227, 219, 198, 30, 231, 33, 214, 78, 171, 140, 203, 185, 82, 71, 67, 24, 242, 1, 97, 194, 186, 57, 68, 54, 103, 42, 147, 91, 180, 12, 0, 151, 231, 198, 181, 206, 231, 140, 29, 147, 24, 232, 76, 106, 47, 143, 130, 34, 144, 228, 228, 75, 29, 40, 129, 132, 82, 21, 223, 7, 33, 224, 158, 8, 166, 84, 214, 142, 224, 243, 33, 248, 219, 109, 99, 11, 252, 229, 45, 141, 201, 17, 216, 230, 58, 89, 107, 140, 110, 74, 147, 143, 42, 50};

    //std::vector <unsigned char> div_int (4);  //divided int
    unsigned char ch = 0, *div_int = NULL;
    div_int = (unsigned char*) calloc (4, 1);

    if (div_int == NULL)
    {
      return 'a';                //allocation error
    }



    int f_size = f.in_avail ();

    for (int i = 0; i < 256; i++)
    {
      ch = f.sbumpc ();
      if (ch != sign[i])
      {
        f.close ();
        return 'r';             //recognizion error
      }
    }


    for (int i = 0; i < 4; i++)
    {
      div_int[i] = f.sbumpc ();
    }
    unsigned int size = convert_chars_to_int (div_int);


    ;

    if (size != f_size)
    {
      f.close ();
      return 's';               //sizes don't match
    }


    for (int i = 0; i < 4; i++)
    {
      div_int[i] = f.sbumpc ();
    }
    *x = convert_chars_to_int (div_int);



    for (int i = 0; i < 4; i++)
    {
      div_int[i] = f.sbumpc ();
    }
    *y = convert_chars_to_int (div_int);


    *xy = (*x) * (*y);



    for (int i = 0; i < 4; i++)
    {
      div_int[i] = f.sbumpc ();
    }
    *counter = convert_chars_to_int (div_int);


    for (int i = 0; i < 4; i++)
    {
      div_int[i] = f.sbumpc ();
    }
    *it_p_color = convert_chars_to_int (div_int);
    *step = 255.0 / *it_p_color;




    if (*r != NULL)
    {
      free (*r);
    }


    if (*g != NULL)
    {
      free (*g);
    }


    if (*b != NULL)
    {
      free (*b);
    }


    *r = NULL;
    *g = NULL;
    *b = NULL;


    *r = (float*) calloc (*xy, sizeof (float));
    *g = (float*) calloc (*xy, sizeof (float));
    *b = (float*) calloc (*xy, sizeof (float));



    if (*r == NULL || *g == NULL || *b == NULL)
    {
      return 'a'; //allocation error
    }


    float read_data;


    for (int i = 0; i < *xy; i++)
    {
      (*r)[i] = (float) f.sbumpc ();
    }



    for (int i = 0; i < *xy; i++)
    {
      (*g)[i] = (float) f.sbumpc ();
    }


    for (int i = 0; i < *xy; i++)
    {
      (*b)[i] = (float) f.sbumpc ();
    }


  } else
  {
    return 'f';     //couldn't open file
  }

  f.close ();
  return 'n';       //normal
}
