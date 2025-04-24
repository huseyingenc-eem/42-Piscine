
#include <unistd.h>

void ft_putchar(char str)
{
	write(1,&str,1);
	
}

int		ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void last_word(char *str)
{

	while (*str)
		str++;
	str--;

	while (ft_isblank(*str))
		str--;

	while (*str && !ft_isblank(*str))
		str--;
	
	str++;
	while (*str && !ft_isblank(*str))
	{
		ft_putchar(*str);
		str++;
	}
}




int main(int argc, char *argv[])
{

	if (argc == 2)
		last_word(argv[1]);
	
	ft_putchar('\n');
	return 0;
}