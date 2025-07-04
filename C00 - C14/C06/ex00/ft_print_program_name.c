/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 09:55:03 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/29 09:58:09 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

int	main(int argc, char *argv[])
{
	if (argc >= 1)
		write(1, argv[0], ft_strlen(argv[0]));
	write(1, "\n", 1);
	return (0);
}
