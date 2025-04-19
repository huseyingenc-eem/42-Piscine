#include <unistd.h>

void ft_putchar(char c);

/// @brief 
/// @param first ilk karekter 
/// @param middle ortadaki karekterler
/// @param last   son karekter
/// @param width  genişlik
void print_line(char first, char middle, char last, int width)
{
    int i;

    i=0;
    if (width >=1)
    {
        ft_putchar(first);
        i++;
        while (i <width-1)
        {
            ft_putchar(middle);
            i++;
        }
        if (width > 1)
        {
            ft_putchar(last);
        }
        ft_putchar('\n');
    }
    
    
}






void rush(int x ,int y)
{
    int i;

    i=0;
    if (y >=1 && x>=1)
    {
        print_line('A','B','C',x);
        i++;
        while (i < y-1)
        {
            print_line('B',' ','B',x);
            i++;
        }
        if (y>1)
        {
            print_line('A','B','C',x);
        }
        
        
    }
    
    
}