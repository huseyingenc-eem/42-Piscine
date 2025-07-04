/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:27:19 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/29 12:27:32 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	total_length(int size, char **strs, char *sep)
{
	int	total;
	int	i;

	total = 0;
	i = 0;
	while (i < size)
	{
		total += ft_strlen(strs[i]);
		i++;
	}
	total += (size - 1) * ft_strlen(sep);
	return (total);
}

void	fill_joined_string(char *tab, char **strs, char *sep, int size)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (++i < size)
	{
		j = -1;
		while (strs[i][++j])
			tab[k++] = strs[i][j];
		if (i < size - 1)
		{
			j = -1;
			while (sep[++j])
				tab[k++] = sep[j];
		}
	}
	tab[k] = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*tab;
	int		len;

	if (size <= 0)
	{
		tab = (char *)malloc(sizeof(char));
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	len = total_length(size, strs, sep);
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	fill_joined_string(tab, strs, sep, size);
	return (tab);
}
