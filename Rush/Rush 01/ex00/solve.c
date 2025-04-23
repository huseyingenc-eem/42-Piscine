/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:22:13 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:30:13 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

static int	try_number(int **grid, t_skyscrapers_views *views, t_position pos)
{
	grid[pos.row][pos.col] = pos.num;
	if (check_partial_solution(grid, views, pos.row, pos.col))
	{
		if (solve(grid, views))
			return (1);
	}
	grid[pos.row][pos.col] = '0';
	return (0);
}

int	solve(int **grid, t_skyscrapers_views *views)
{
	int			row;
	int			col;
	char		num;
	t_position	pos;

	if (is_grid_filled(grid))
		return (is_solution_valid(grid, views));
	find_best_empty_cell(grid, &row, &col);
	if (row == -1)
		return (is_solution_valid(grid, views));
	num = '1';
	while (num <= '0' + SIZE)
	{
		if (is_valid(grid, row, col, num))
		{
			pos = (t_position){row, col, num};
			if (try_number(grid, views, pos))
				return (1);
		}
		num++;
	}
	return (0);
}
