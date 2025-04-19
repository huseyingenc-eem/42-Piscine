
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
#include <stdio.h>

int main(void)
{
    char str1[] = "merhaba";
    char str2[] = "merhaba";
    printf("%d", ft_strcmp(str1,str2));    
    return 0;
}
