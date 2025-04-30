/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:25:47 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 07:30:24 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

static int	process_single_input(int fd)
{
	t_map_info	*map_info;
	t_square	bsq_result;

	map_info = read_map(fd);
	if (map_info == NULL)
	{
		return (1);
	}
	bsq_result = solve_bsq(map_info);
	display_result(map_info, bsq_result);
	free_map_info(map_info);
	return (0);
}

static int	process_file(char *filename)
{
	int	fd;
	int	status;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_error("map error\n");
		return (1);
	}
	status = process_single_input(fd);
	close(fd);
	return (status);
}

static int	process_multiple_files(int argc, char **argv)
{
	int	i;
	int	overall_status;
	int	current_status;

	i = 1;
	overall_status = 0;
	while (i < argc)
	{
		if (i > 1)
			write(1, "\n", 1);
		current_status = process_file(argv[i]);
		if (current_status != 0)
			overall_status = 1;
		i++;
	}
	return (overall_status);
}

int	main(int argc, char **argv)
{
	int	status;

	status = 0;
	if (argc == 1)
	{
		status = process_single_input(0);
	}
	else
	{
		status = process_multiple_files(argc, argv);
	}
	return (status);
}
