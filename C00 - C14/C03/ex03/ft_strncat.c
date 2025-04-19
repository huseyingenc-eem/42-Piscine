
char *ft_strncat(char *dest, char *src, unsigned int nb)
{
    char* start;
    unsigned int size;
    start=dest;
	while (*dest)
        dest++;

    size=0;
    while (*src && size < nb)
    {
        *dest++ = *src++;
        size++;
    }
    
    *dest = '\0';
    
    return start;
}


#include <stdio.h>

int main(void)
{
    char str1[] = "merhaba";
    char str2[] = "sevval";
    printf("%s", ft_strncat(str1,str2,4));    
    return 0;
}