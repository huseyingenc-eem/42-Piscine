/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:51:50 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:54:04 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

static void	paint_square_on_grid(t_map_info *map, t_square bsq)
{
	int	start_y;
	int	start_x;
	int	y;
	int	x;

	if (bsq.size == 0)
		return ;
	start_y = bsq.y - bsq.size + 1;
	start_x = bsq.x - bsq.size + 1;
	y = start_y;
	while (y <= bsq.y)
	{
		x = start_x;
		while (x <= bsq.x)
		{
			if (y >= 0 && y < map->lines && x >= 0 && x < map->cols)
				map->grid[y][x] = map->full;
			x++;
		}
		y++;
	}
}

static void	print_final_grid(t_map_info *map)
{
	int	y;

	y = 0;
	while (y < map->lines)
	{
		write(1, map->grid[y], map->cols);
		write(1, "\n", 1);
		y++;
	}
}

void	display_result(t_map_info *map_info, t_square bsq)
{
	paint_square_on_grid(map_info, bsq);
	print_final_grid(map_info);
}
