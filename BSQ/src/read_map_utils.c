/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:52:55 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 05:53:16 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

void	free_partial_grid(char **grid, int lines_filled)
{
	int	i;

	i = 0;
	while (i < lines_filled)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	read_single_line(int fd, char *buffer, int buffer_size)
{
	int		bytes_read;
	int		total_bytes;
	char	c;

	total_bytes = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (c == '\n')
			break ;
		if (total_bytes < buffer_size - 1)
			buffer[total_bytes++] = c;
		else
			return (-1);
		bytes_read = read(fd, &c, 1);
	}
	buffer[total_bytes] = '\0';
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0 && total_bytes == 0)
		return (-2);
	return (total_bytes);
}

int	check_config_chars(t_map_info *map_info)
{
	if (map_info->empty == map_info->obstacle)
		return (0);
	if (map_info->empty == map_info->full)
		return (0);
	if (map_info->obstacle == map_info->full)
		return (0);
	return (1);
}

int	parse_config_line(char *buffer, int len, t_map_info *map_info)
{
	int	i;
	int	num_part_len;

	if (len < 4)
		return (0);
	map_info->empty = buffer[len - 3];
	map_info->obstacle = buffer[len - 2];
	map_info->full = buffer[len - 1];
	if (!check_config_chars(map_info))
		return (0);
	num_part_len = len - 3;
	i = 0;
	map_info->lines = 0;
	while (i < num_part_len)
	{
		if (buffer[i] < '0' || buffer[i] > '9')
			return (0);
		map_info->lines = map_info->lines * 10 + (buffer[i] - '0');
		i++;
	}
	if (map_info->lines <= 0)
		return (0);
	map_info->cols = 0;
	map_info->grid = NULL;
	return (1);
}

int	validate_grid_line(char *line, int len, t_map_info *map)
{
	int	i;

	i = 0;
	if (map->cols == 0)
	{
		if (len == 0)
			return (0);
		map->cols = len;
	}
	else if (len != map->cols)
		return (0);
	while (i < len)
	{
		if (line[i] != map->empty && line[i] != map->obstacle)
			return (0);
		i++;
	}
	return (1);
}
