#include <stdio.h>

void ft_swap(int *a, int *b)
{
    int temp;

    temp =*a;
    *a=*b;
    *b=temp;
}

void ft_rev_int_tab(int *tab, int size)
{
    int i;

    i=0;
	while (i< size / 2)
	{
		ft_swap(&tab[i], &tab[size -i -1 ]);
		i++;
	}
}
