/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:35:58 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:35:59 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	count_visible(int *a)
{
	int	i;
	int	visible;
	int	max_height;

	i = 0;
	visible = 0;
	max_height = 0;
	while (i < SIZE)
	{
		if (a[i] > max_height)
		{
			visible++;
			max_height = a[i];
		}
		i++;
	}
	return (visible);
}

void	fill_row_arrays(int **grid, int row, int *forward, int *reverse)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		forward[i] = grid[row][i] - '0';
		reverse[SIZE - 1 - i] = grid[row][i] - '0';
		i++;
	}
}

int	is_row_valid(int **grid, int row, int left_view, int right_view)
{
	int	left_visible;
	int	right_visible;
	int	forward_row[SIZE];
	int	reversed_row[SIZE];

	fill_row_arrays(grid, row, forward_row, reversed_row);
	left_visible = count_visible(forward_row);
	right_visible = count_visible(reversed_row);
	return (left_visible == left_view && right_visible == right_view);
}
