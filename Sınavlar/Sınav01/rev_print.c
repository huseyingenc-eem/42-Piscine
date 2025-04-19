#include <unistd.h>


void ft_putchar(char c)
{
    write(1,&c,1);
}



int ft_strlen(char *str)
{
    int counter;

    counter=0;
    while (str[counter])
        counter++;
    
    return (counter);
}


int main(int argc, char *argv[])
{
    int lenght;
    if (argc ==2)
    {
        lenght = ft_strlen(argv[1]);
        while (lenght--)
            ft_putchar(argv[1][lenght]);
    }
    ft_putchar('\n');
    return 0;
}