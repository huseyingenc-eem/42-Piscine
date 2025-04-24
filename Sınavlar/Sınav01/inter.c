
#include <stdio.h>
#include <unistd.h>
void ft_putchar(char str)
{
	write(1,&str,1);
	
}

int comp(char *src, char c, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		if (src[i]== c)
			return 0;
		i++;
	}
	return 1;
}

void inter(char *src, char * to_find)
{
	int index;
	int jndex;

	index = 0;
	while (src[index])
	{
		if (comp(src,src[index],index) == 1)
		{
			jndex=0;
			while (to_find[jndex])
			{
				if (src[index] == to_find[jndex])
				{
					ft_putchar(src[index]);
					break;
				}
				jndex++;
			}
		}
		index++;
	}
}

int main(int argc, char *argv[])
{

	if (argc == 3)
		inter(argv[1], argv[2]);
	
	ft_putchar('\n');
	return 0;
}//mam