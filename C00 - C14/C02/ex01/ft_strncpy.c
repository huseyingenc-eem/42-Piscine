
char *ft_strncpy(char *dest, char *src, unsigned int n)
{
    char* ptr;

    ptr = dest;
    while (n && *src)
    {
        *dest++=*src++;
        n--;
    }
    while (n)
	{
		*dest++ = '\0';
		n--;
	}
	return (ptr);
}