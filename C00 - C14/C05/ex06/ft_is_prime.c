int	ft_is_prime(int nb)
{
	int	dividing;

	dividing = 2;
	if (nb < 2)
		return (0);
	while (dividing < nb)
	{
		if (nb % dividing == 0)
			return (0);
		dividing++;
	}
	return (1);
}
#include<stdio.h>
int main()
{
	printf("%d\n",ft_is_prime(2));
	printf("%d\n",ft_is_prime(15));
	printf("%d\n",ft_is_prime(0));
	printf("%d\n",ft_is_prime(1));
	return 0;
}