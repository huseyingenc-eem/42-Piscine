/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:26:22 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/30 06:26:49 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_map_info
{
	int		lines;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map_info;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
}	t_square;

typedef struct s_pos
{
	int	row;
	int	col;
}	t_pos;

void		init_pos(t_pos *p);
t_map_info	*read_map(int fd);
void		free_map_info(t_map_info *map_info);
void		ft_putstr_error(char *str);
int			ft_strlen(char *str);
t_square	solve_bsq(t_map_info *map_info);
void		display_result(t_map_info *map_info, t_square bsq);

#endif