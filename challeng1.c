#include <stdio.h>

int main() {

  enum Companies { GOOGLE, META, XEROX, YAHOO, EBAY, MICROSOFT };
  
  enum Companies google, xerox, ebay;

  google = GOOGLE;
  xerox = XEROX;
  ebay = EBAY;

  printf("%d\n%d\n%d\n", xerox, google, ebay);
  
  double d = 2.35857565;

  printf("%e => e format spicifyer \n", d);
  printf("%g => g format spicifyer \n", d);
  
  return 0;
}

