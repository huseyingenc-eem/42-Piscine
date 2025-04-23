/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:35:40 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:35:42 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

void	fill_col_arrays(int **grid, int col, int *forward, int *reverse)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		forward[i] = grid[i][col] - '0';
		reverse[SIZE - 1 - i] = grid[i][col] - '0';
		i++;
	}
}

int	is_col_valid(int **grid, int col, int top_view, int bottom_view)
{
	int	top_visible;
	int	bottom_visible;
	int	forward_col[SIZE];
	int	reversed_col[SIZE];

	fill_col_arrays(grid, col, forward_col, reversed_col);
	top_visible = count_visible(forward_col);
	bottom_visible = count_visible(reversed_col);
	return (top_visible == top_view && bottom_visible == bottom_view);
}
