char *ft_strupcase(char *str)
{
    char	*ptr;

	ptr = str;

    while (*ptr)
	{
		if (*ptr >= 'a' && *ptr <= 'z')
			*ptr -= 32;
		ptr++;
	}
	return (str);
}