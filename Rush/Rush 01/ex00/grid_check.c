/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:07:00 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:36:33 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	is_valid(int **grid, int row, int col, int num_char)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (i != col && grid[row][i] == num_char)
			return (0);
		if (i != row && grid[i][col] == num_char)
			return (0);
		i++;
	}
	return (1);
}

int	is_grid_filled(int **grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			if (grid[i][j] == '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_solution_valid(int **grid, t_skyscrapers_views *views)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!is_row_valid(grid, i, views->left[i], views->right[i]))
			return (0);
		if (!is_col_valid(grid, i, views->top[i], views->bottom[i]))
			return (0);
		i++;
	}
	return (1);
}
