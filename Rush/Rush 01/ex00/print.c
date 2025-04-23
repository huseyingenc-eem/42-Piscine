/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:33:02 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:33:34 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_err(char *msg)
{
	int		msg_len;
	char	*start;

	if (msg == NULL)
		return ;
	start = msg;
	msg_len = 0;
	while (*msg)
	{
		msg_len++;
		msg++;
	}
	write(2, start, msg_len);
}

int	ft_parse_int(char **string_ptr, int *value)
{
	int		result;
	char	*p;

	p = *string_ptr;
	result = 0;
	while (*p == ' ' || *p == '\t')
		p++;
	if (!(*p >= '0' && *p <= '9'))
	{
		*string_ptr = p;
		return (0);
	}
	while (*p >= '0' && *p <= '9')
		result = result * 10 + (*p++ - '0');
	while (*p == ' ' || *p == '\t')
		p++;
	*value = result;
	*string_ptr = p;
	return (1);
}
