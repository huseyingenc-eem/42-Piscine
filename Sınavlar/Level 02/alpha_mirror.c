

#include <unistd.h>
void ft_putchar(char value)
{
    write(1,&value,1);
}

int		ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char    ft_alpha_mirror(char value)
{
	return (value = (value >= 'A' && value <= 'Z') ? 'Z' - (value - 'A') : 'z' - (value - 'a'));
}

void ft_alpha(char *src)
{
    while (*src)
    {
        if (ft_isalpha(*src))
            ft_putchar(ft_alpha_mirror(*src));
        else
            ft_putchar(*src);

        src++;
    }
    
}


int main(int argc, char *argv[])
{
    
    if (argc == 2)
        ft_alpha(argv[1]);
    
    
    ft_putchar('\n');
    return 0;
}