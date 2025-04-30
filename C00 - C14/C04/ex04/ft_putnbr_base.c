/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:20:53 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/28 10:17:59 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_check_base(char *base)
{
	int	i;
	int	j;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-'
			|| base[i] < 32 || base[i] == 127)
			return (0);
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_print_number(long nbr, char *base, int size)
{
	char	box[32];
	int		i;

	i = 0;
	if (nbr == 0)
	{
		ft_putchar(base[0]);
		return ;
	}
	while (nbr > 0)
	{
		box[i] = base[nbr % size];
		nbr = nbr / size;
		i++;
	}
	while (--i >= 0)
		ft_putchar(box[i]);
}

void	ft_putnbr_base(int nbr, char *base)
{
	long	long_n;
	int		size;

	if (!ft_check_base(base))
		return ;
	size = ft_strlen(base);
	long_n = nbr;
	if (long_n < 0)
	{
		ft_putchar('-');
		long_n *= -1;
	}
	ft_print_number(long_n, base, size);
}
