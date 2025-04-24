#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int	i;

	i = 128;
	while (i)
	{
		if (octet & i)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i /= 2;
	}
}

int		main(void)
{//
	int n = 58;
	print_bits(n);
	write(1, "\n", 1);
}