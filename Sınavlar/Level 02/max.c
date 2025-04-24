#include <stdio.h>//
#include <stdlib.h>//
int		max(int* tab, unsigned int len)
{
    int max;
    int index;
    
    if (!len)
        return 0;
    
    index = 0;
    max = tab[0];
    while (index < len)
    {
        if (tab [index] > max)
            max = tab [index];
        index++;
    }
    return max;
}

int		main(void)
{
	int	tab [10] = {10,20,30,40,200,13,15,24,10,5};
    int size = 10;
	printf("%d", max(tab, 10));
	return (0);
}