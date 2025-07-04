/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:13:17 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/29 10:15:18 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	put_char(char c)
{
	write(1, &c, 1);
}

int	ft_strcmp(char *lhs, char *rhs)
{
	while (*lhs && *rhs)
	{
		if (*lhs != *rhs)
			return (*lhs - *rhs);
		lhs++;
		rhs++;
	}
	return (*lhs - *rhs);
}

void	swap(char **lhs, char **rhs)
{
	char	*tmp;

	tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
}

void	sort_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc - 1)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
				swap(&argv[i], &argv[j]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	char	*ptr;

	sort_args(argc, argv);
	i = 1;
	while (i < argc)
	{
		ptr = argv[i];
		while (*ptr)
			put_char(*ptr++);
		put_char('\n');
		i++;
	}
	return (0);
}
