
char *ft_strstr(char *str, char *to_find)
{
    char* start;
    
    if (!*to_find)
		return (str);
    
    
    start=str;
    while (*str==*to_find)
    {
        str++;
        to_find++;
    }


    
    return start;
}


#include <stdio.h>

int main(void)
{
    char a= 'a';
    
    char str1[] = "merhaba";

    char str2[] = "sevval";
    printf("%s", ft_strncat(str1,str2,4));    
    return 0;
}