
int ft_recursive_power(int nb, int power)
{
    int		sayi;

	sayi = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 0)
	{
		return (nb * ft_recursive_power(nb, power - 1));
	}
	return (sayi); 
}