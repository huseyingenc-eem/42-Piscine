/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:22:57 by hayildiz          #+#    #+#             */
/*   Updated: 2025/04/13 21:11:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	print_line(char a, char b, char c, int x)
{
	int	i;

	i = 0;
	if (x >= 1)
	{
		ft_putchar(a);
		i++;
		while (i < x - 1)
		{
			ft_putchar(b);
			i++;
		}
		if (x > 1)
			ft_putchar(c);
		ft_putchar('\n');
	}
}

void	rush(int x, int y)
{
	int	i;

	i = 0;
	if (y >= 1 && x >= 1)
	{
		print_line('A', 'B', 'C', x);
		i++;
		while (i < y - 1)
		{
			print_line('B', ' ', 'B', x);
			i++;
		}
		if (y > 1)
			print_line('A', 'B', 'C', x);
	}
}
