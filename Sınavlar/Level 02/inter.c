
#include <unistd.h>
void ft_putchar(char value)
{
    write(1,&value,1);
}

int check(char* src, char value, char index)
{
    int i;

    i = 0;
    while (i < index)
    {
        if (src[i] == value)
            return 0;
        i++;
    }
    return 1;
}

void inter(char *src, char* to_find)
{
    int index;
    int jndex;

    index = 0;
    while (src[index])
    {
        if (check(src,src[index],index))
        {
            jndex =0;
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
}
