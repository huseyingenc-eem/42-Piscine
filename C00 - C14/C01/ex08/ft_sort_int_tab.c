void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	first_select;
	int	last_select;

	first_select = 0;
	while (first_select < size - 1)
	{
		last_select = first_select + 1;
		while (last_select < size)
		{
			if (tab[last_select] < tab[first_select])
                ft_swap(&tab[first_select], &tab[last_select]);

			last_select++;
		}
		first_select++;
	}
}

