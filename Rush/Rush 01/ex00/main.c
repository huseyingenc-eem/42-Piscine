/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:16:58 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:17:09 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	validate_args(int argc)
{
	if (argc != 2)
	{
		ft_print_err("Error: Wrong number of arguments\n");
		return (0);
	}
	return (1);
}

static int	init_and_solve(char *input)
{
	t_skyscrapers_views	views;
	int					**grid;

	if (!parse_views(input, &views))
	{
		ft_print_err("Error: Invalid input\n");
		return (1);
	}
	grid = create_grid();
	if (!grid)
	{
		ft_print_err("Error: Memory allocation failed\n");
		return (1);
	}
	if (solve(grid, &views))
		print_grid(grid);
	else
		ft_print_err("Error: No solution found\n");
	free_grid(grid);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (!validate_args(argc))
		return (1);
	return (init_and_solve(argv[1]));
}
