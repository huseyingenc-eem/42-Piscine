
#include <unistd.h>
void ft_putchar(char value)
{
    write(1,&value,1);
}

int not_seen_before(char* src, char value, char index)
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

void ft_union(char * str1, char* str2)
{
    int index;
    int jndex;


    index = -1;
    while (str1[++index])
    {
        if (not_seen_before(str1, str1[index], index))
            ft_putchar(str1[index]);
    }
    jndex=-1;
    while (str2[++jndex])
    {
        if (not_seen_before(str1, str2[jndex], index) 
            && not_seen_before(str2, str2[jndex], jndex))
        {
            ft_putchar(str2[jndex]);
        }
        
    }
    
    

}


int main(int argc, char *argv[])
{
    
    if (argc == 3)
        ft_union(argv[1], argv[2]);
    
    
    ft_putchar('\n');
    return 0;
}
