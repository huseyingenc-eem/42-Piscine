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

void	print_line(char first, char middle, char last, int width)
{
	int	i;

	i = 0;
	if (width >= 1)
	{
		ft_putchar(first);
		i++;
		while (i < width - 1)
		{
			ft_putchar(middle);
			i++;
		}
		if (width > 1)
			ft_putchar(last);
		ft_putchar('\n');
	}
}
/// @brief Yazı yazdırma
/// @param x  -> width 
/// @param y  -> height 
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
