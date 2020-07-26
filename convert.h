#include <string>
#include <cmath>

unsigned int convert_chars_to_int (unsigned char* vec) //assemles an integer from separate bytes
{
  unsigned int x = 0;
  for (int i = 0; i < 4; i++)
  {
    x += vec[i] * pow (256, i);
  }
  return x;
}



void convert_int_to_chars (unsigned int x, unsigned char* vec) //divides an integer into separate bytes
{
  for (int i = 0; i < 4; i++)
  {
    vec[i] = x % 256;
    x /= 256;
  }
}
// 15
