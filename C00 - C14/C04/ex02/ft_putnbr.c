/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 07:29:51 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/24 15:04:00 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	char	buffer[12];
	long	number;
	int		index;

	number = nb;
	if (number == 0)
	{
		ft_putchar('0');
		return ;
	}
	if (number < 0)
	{
		ft_putchar('-');
		number = -number;
	}
	index = 0;
	while (number > 0)
	{
		buffer[index++] = (number % 10) + '0';
		number /= 10;
	}
	while (index--)
	{
		ft_putchar(buffer[index]);
	}
}
