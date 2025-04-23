int	ft_sqrt(int nb)
{
	int	counter;
	int	step;

	if (nb < 0)
		return (0);
	counter = 0;
	step = 1;
	while (nb > 0)
	{
		nb -= step;
		step += 2;
		counter++;
	}
	if (nb == 0)
		return (counter);
	else
		return (0);
}
