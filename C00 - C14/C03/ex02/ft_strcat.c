char *ft_strcat(char *dest, char *src)
{
    char* start;

    start=dest;
	while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;
    
    *dest = '\0';
    
    return start;
}
#include <stdio.h>

int main(void)
{
    char str1[] = "merhaba";
    char str2[] = "sevval";
    printf("%s", ft_strcat(str1,str2));    
    return 0;
}
