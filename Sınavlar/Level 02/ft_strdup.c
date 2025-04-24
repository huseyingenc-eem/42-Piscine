
#include <stdlib.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char    *ft_strdup(char *src)
{
    char* start;
    char* dest;
    int size;

    size = 0;
    while (src[size])
        size++;
    
    dest = (char *)malloc((size+1) * sizeof(char));

    if (!dest)
        return NULL;
    
    start =dest;
    while (*src)
    {
        *dest++ = *src++;
    }
    *dest= '\0';
    return (start);
}

// int	main(void)
// {
// 	char	*original;
// 	char	*copy;

// 	original = "42 Kocaeli";
// 	copy = ft_strdup(original);
// 	if (copy)
// 	{
// 		ft_putstr("Original: ");
// 		ft_putstr(original);
// 		ft_putstr("\nCopy    : ");
// 		ft_putstr(copy);
// 		ft_putstr("\n");
// 		free(copy);
// 	}
// 	else
// 		ft_putstr("Memory allocation failed.\n");
// 	return (0);
// }