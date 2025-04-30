/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 05:53:48 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 05:53:53 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* read_map.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/04/30 05:48:39 by your_login        #+#    #+#             */
/* Updated: 2025/04/30 05:48:40 by your_login       ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../includes/bsq.h"

int		read_single_line(int fd, char *buffer, int buffer_size);
int		parse_config_line(char *buffer, int len, t_map_info *map_info);
int		validate_grid_line(char *line, int len, t_map_info *map);
void	free_partial_grid(char **grid, int lines_filled);

static char	*copy_line(char *buffer, int len)
{
	char	*line_copy;
	int		i;

	line_copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!line_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line_copy[i] = buffer[i];
		i++;
	}
	line_copy[i] = '\0';
	return (line_copy);
}

static int	process_grid_lines(int fd, t_map_info *map)
{
	char	buffer[4096];
	int		line_idx;
	int		len;
	char	*current_line;

	line_idx = 0;
	while (line_idx < map->lines)
	{
		len = read_single_line(fd, buffer, 4096);
		if (len < 0 || !validate_grid_line(buffer, len, map))
		{
			free_partial_grid(map->grid, line_idx);
			return (0);
		}
		current_line = copy_line(buffer, map->cols);
		if (!current_line)
		{
			free_partial_grid(map->grid, line_idx);
			return (0);
		}
		map->grid[line_idx] = current_line;
		line_idx++;
	}
	return (1);
}

static int	allocate_grid(t_map_info *map)
{
	map->grid = (char **)malloc(sizeof(char *) * map->lines);
	if (!map->grid)
		return (0);
	return (1);
}

void	free_map_info(t_map_info *map_info)
{
	if (!map_info)
		return ;
	if (map_info->grid)
		free_partial_grid(map_info->grid, map_info->lines);
	free(map_info);
}

t_map_info	*read_map(int fd)
{
	t_map_info	*map_info;
	char		buffer[1024];
	int			len;

	map_info = (t_map_info *)malloc(sizeof(t_map_info));
	if (!map_info)
		return (ft_putstr_error("map error\n"), NULL);
	len = read_single_line(fd, buffer, 1024);
	if (len <= 0 || !parse_config_line(buffer, len, map_info))
	{
		free(map_info);
		return (ft_putstr_error("map error\n"), NULL);
	}
	if (!allocate_grid(map_info))
	{
		free(map_info);
		return (ft_putstr_error("map error\n"), NULL);
	}
	if (!process_grid_lines(fd, map_info))
	{
		free(map_info);
		return (ft_putstr_error("map error\n"), NULL);
	}
	return (map_info);
}
