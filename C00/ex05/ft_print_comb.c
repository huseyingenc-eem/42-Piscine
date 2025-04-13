#include <unistd.h>

void ft_print_comb(void)
{
    int x='0';
    int y='0';
    int z='0';

    while (x<='7')
    {
        y=x+1; // char setinde bir eklendi 0 dan sonra 1 gelir.
        while (y <='8')
        {
            z=y+1;

            while (z<='9')
            {
                write(1,&x,1);
                write(1,&y,1);
                write(1,&z,1);

                if (x != '7')
                    write(1, ", ",2);
                
                z++;
            }
            y++;
        }
        x++;
    }
}
