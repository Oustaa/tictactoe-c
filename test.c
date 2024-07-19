#include <stdio.h>
#include <stdbool.h>

enum primaryColors
{
  red,
  yellow,
  blue
};

void printColor(enum primaryColors color)
{
  switch (color)
  {
  case red:
    printf("Red\n");
    break;
  case yellow:
    printf("Yellow\n");
    break;
  case blue:
    printf("Blue\n");
    break;
  default:
    printf("Invalid color\n");
  }
}

int main(int argc, char **argv)
{

  // enum primaryColors color1, color2;

  // color1 = red;
  // color2 = blue;

  // printf("Primary is %d\n", color1);

  // printColor(color1);
  // printColor(color2);

  printf("%d\n", argc);
  printf("%s\n", argv[0]);
  printf("%s\n", argv[1]);

  return 0;
}