char *ft_strupcase(char *str)
{
    char	*ptr;

	ptr = str;

    while (*ptr)
	{
		if (*ptr >= 'A' && *ptr <= 'Z')
			*ptr += 32;
		ptr++;
	}
	return (str);
}