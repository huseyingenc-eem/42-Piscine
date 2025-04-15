
char *ft_strcpy(char *dest, char *src)
{
    char* ptr;

    ptr = dest;
    while (*src)
    {
        *dest++=*src++;
    }
    *dest = '\0';
	return (ptr);
}
