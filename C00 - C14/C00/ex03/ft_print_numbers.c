#include <unistd.h>

void ft_print_numbers(void) {
    char sayi;
  
    sayi = '0';
    while (sayi <= '9') {
      write(1, &sayi, 1);
      sayi++;
    }
  }
