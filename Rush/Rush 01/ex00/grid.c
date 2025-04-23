/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:05:43 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:13:33 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

void	print_grid(int **grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			ft_putchar(grid[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int	**create_grid_rows(void)
{
	int	**matrix;
	int	i;

	matrix = (int **)malloc(SIZE * sizeof(int *));
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < SIZE)
	{
		matrix[i] = NULL;
		i++;
	}
	return (matrix);
}

int	init_grid_columns(int **matrix)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < SIZE)
	{
		matrix[i] = (int *)malloc(SIZE * sizeof(int));
		if (!matrix[i])
		{
			k = 0;
			while (k < i)
				free(matrix[k++]);
			free(matrix);
			return (0);
		}
		j = 0;
		while (j < SIZE)
			matrix[i][j++] = '0';
		i++;
	}
	return (1);
}

void	free_grid(int **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < SIZE)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

int	**create_grid(void)
{
	int	**matrix;

	matrix = create_grid_rows();
	if (!matrix)
		return (NULL);
	if (!init_grid_columns(matrix))
		return (NULL);
	return (matrix);
}
