/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:34:26 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:34:27 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	is_row_complete(int **grid, int row)
{
	int	j;

	j = 0;
	while (j < SIZE)
	{
		if (grid[row][j] == '0')
			return (0);
		j++;
	}
	return (1);
}

int	is_col_complete(int **grid, int col)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (grid[i][col] == '0')
			return (0);
		i++;
	}
	return (1);
}

int	check_partial_solution(int **grid, t_skyscrapers_views *views,
		int row, int col)
{
	if (is_row_complete(grid, row)
		&& !is_row_valid(grid, row, views->left[row], views->right[row]))
		return (0);
	if (is_col_complete(grid, col)
		&& !is_col_valid(grid, col, views->top[col], views->bottom[col]))
		return (0);
	return (1);
}
