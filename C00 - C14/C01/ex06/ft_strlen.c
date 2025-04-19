
#include <unistd.h>

int ft_strlen(char *str)
{
    int lenght;

    lenght=0;
    while (str[lenght])
    {
        lenght++;
    }
    return (lenght);
}
