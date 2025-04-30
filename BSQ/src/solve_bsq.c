/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_bsq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:54:13 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:20:56 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

static int	min_of_three(int a, int b, int c)
{
	int	min_val;

	min_val = a;
	if (b < min_val)
		min_val = b;
	if (c < min_val)
		min_val = c;
	return (min_val);
}

static int	calculate_cell_value(t_map_info *map, int **dp, int r, int c)
{
	if (map->grid[r][c] == map->obstacle)
		return (0);
	if (r == 0 || c == 0)
		return (1);
	return (1 + min_of_three(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1]));
}

static void	update_bsq(int current_val, int r, int c, t_square *bsq)
{
	if (current_val > bsq->size)
	{
		bsq->size = current_val;
		bsq->x = c;
		bsq->y = r;
	}
}

static int	**create_dp_matrix(int lines, int cols)
{
	int	**dp_table;
	int	i;

	dp_table = (int **)malloc(sizeof(int *) * lines);
	if (!dp_table)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		dp_table[i] = (int *)malloc(sizeof(int) * cols);
		if (!dp_table[i])
		{
			while (--i >= 0)
				free(dp_table[i]);
			free(dp_table);
			return (NULL);
		}
		i++;
	}
	return (dp_table);
}

t_square	solve_bsq(t_map_info *map_info)
{
	t_square	bsq;
	int			**dp;
	t_pos		pos;

	dp = create_dp_matrix(map_info->lines, map_info->cols);
	if (!dp)
		return ((t_square){.x = 0, .y = 0, .size = 0});
	bsq = (t_square){0, 0, 0};
	init_pos(&pos);
	while (++pos.row < map_info->lines)
	{
		pos.col = -1;
		while (++pos.col < map_info->cols)
		{
			dp[pos.row][pos.col] = calculate_cell_value(map_info, dp,
					pos.row, pos.col);
			update_bsq(dp[pos.row][pos.col], pos.row, pos.col, &bsq);
		}
	}
	pos.row = -1;
	while (++pos.row < map_info->lines)
		free(dp[pos.row]);
	free(dp);
	return (bsq);
}
