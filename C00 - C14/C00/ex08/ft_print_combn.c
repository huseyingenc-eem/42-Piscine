#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_combination(char *digits, int length, int is_last)
{
	int	i;

	i = 0;
	while (i < length)
	{
		ft_putchar(digits[i]);
		i++;
	}
	if (!is_last)
		write(1, ", ", 2);
}
void	generate_combinations(char *digits, int n, int pos, char start)
{
	char	current;

	current = start;
	while (current <= '9')
	{
		digits[pos] = current;
		if (pos == n - 1)
			print_combination(digits, n, digits[0] == ('9' - n + 1));
		else
			generate_combinations(digits, n, pos + 1, current + 1);
        current++;
	}
}


void	ft_print_combn(int n)
{
	char	digits[9];

	if (n < 1 || n > 9)
		return ;
	generate_combinations(digits, n, 0, '0');
}

int	main(void)
{
	ft_print_combn(2);
	write(1, "\n", 1);
	return (0);
}
