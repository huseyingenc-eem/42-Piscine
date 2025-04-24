
#include <unistd.h>
void ft_putchar(char value)
{
    write(1,&value,1);
}


void	ft_wdmatch(char *s1, char *s2)
{
	int len = 0;
	int i = 0;

	while (s1[len])
		++len;
	while (*s2 && i < len)
		(*s2++ == s1[i]) ? ++i : 0;
	if (i == len)
		write(1, s1, len);
}


int main(int argc, char *argv[])
{
    
    if (argc == 3)
        ft_wdmatch(argv[1], argv[2]);
    
    
    ft_putchar('\n');
    return 0;
}