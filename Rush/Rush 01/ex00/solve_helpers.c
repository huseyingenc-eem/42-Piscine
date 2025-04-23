/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:23:47 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:23:48 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	count_valid_options(int **grid, int row, int col)
{
	int		count;
	char	num_char;

	count = 0;
	num_char = '1';
	while (num_char <= '0' + SIZE)
	{
		if (is_valid(grid, row, col, num_char))
			count++;
		num_char++;
	}
	return (count);
}

static int	check_cell(int **grid, int i, int j,
	int *row_col_min_data[3])
{
	int	current_options;

	if (grid[i][j] != '0')
		return (0);
	current_options = count_valid_options(grid, i, j);
	if (current_options <= 0 || current_options >= *row_col_min_data[0])
		return (0);
	*row_col_min_data[0] = current_options;
	*row_col_min_data[1] = i;
	*row_col_min_data[2] = j;
	if (*row_col_min_data[0] == 1)
		return (1);
	return (0);
}

void	find_best_empty_cell(int **grid, int *row, int *col)
{
	int	i;
	int	j;
	int	min_options;
	int	data[3];
	int	*row_col_min_data[3];

	min_options = SIZE + 1;
	data[0] = min_options;
	row_col_min_data[0] = &data[0];
	row_col_min_data[1] = row;
	row_col_min_data[2] = col;
	*row = -1;
	*col = -1;
	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			if (check_cell(grid, i, j, row_col_min_data))
				return ;
			j++;
		}
		i++;
	}
}
