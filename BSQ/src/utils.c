/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:50:25 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:21:35 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	init_pos(t_pos *p)
{
	p->row = -1;
	p->col = -1;
}
