
int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	while (n-- && *s1++ && *s2++ && (*s1 == *s2))

	if (n == 0)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
#include <stdio.h>

int main(void)
{
    char str1[] = "merhaba";
    char str2[] = "meraaba";
    printf("%d", ft_strncmp(str1,str2,4));    
    return 0;
}
