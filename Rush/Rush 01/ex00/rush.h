/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:18:21 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:18:24 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

# include <unistd.h>
# include <stdlib.h>

# define SIZE 4

typedef struct s_skyscrapers_views {
	int	top[SIZE];
	int	bottom[SIZE];
	int	left[SIZE];
	int	right[SIZE];
}	t_skyscrapers_views;

typedef struct s_position {
	int		row;
	int		col;
	char	num;
}	t_position;

void	ft_putchar(char c);
void	ft_print_err(char *msg);
int		ft_parse_int(char **string_ptr, int *value);
int		parse_views_part(char **pos, int *views_arr);
int		validate_views_values(t_skyscrapers_views *views);
int		parse_views(char *input_string, t_skyscrapers_views *views);

void	print_grid(int **grid);
int		**create_grid_rows(void);
int		init_grid_columns(int **matrix);
void	free_grid(int **grid);
int		**create_grid(void);

int		is_valid(int **grid, int row, int col, int num_char);
int		count_visible(int *a);
void	fill_row_arrays(int **grid, int row, int *forward, int *reverse);
int		is_row_valid(int **grid, int row, int left_view, int right_view);
void	fill_col_arrays(int **grid, int col, int *forward, int *reverse);
int		is_col_valid(int **grid, int col, int top_view, int bottom_view);
int		is_grid_filled(int **grid);
int		is_solution_valid(int **grid, t_skyscrapers_views *views);
int		is_row_complete(int **grid, int row);
int		is_col_complete(int **grid, int col);
int		check_partial_solution(int **grid, t_skyscrapers_views *views,
			int row, int col);

int		count_valid_options(int **grid, int row, int col);
void	find_best_empty_cell(int **grid, int *row, int *col);
int		solve(int **grid, t_skyscrapers_views *views);

#endif