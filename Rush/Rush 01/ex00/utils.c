/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkinali <bkinali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:32:45 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/20 23:32:46 by bkinali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

int	parse_views_part(char **pos, int *views_arr)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_parse_int(pos, &views_arr[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_views_values(t_skyscrapers_views *views)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (views->top[i] < 1 || views->top[i] > SIZE
			|| views->bottom[i] < 1 || views->bottom[i] > SIZE
			|| views->left[i] < 1 || views->left[i] > SIZE
			|| views->right[i] < 1 || views->right[i] > SIZE)
			return (0);
		i++;
	}
	return (1);
}

int	parse_views(char *input_string, t_skyscrapers_views *views)
{
	char	*current_pos;

	if (input_string == NULL || views == NULL)
		return (0);
	current_pos = input_string;
	if (!parse_views_part(&current_pos, views->top))
		return (0);
	if (!parse_views_part(&current_pos, views->bottom))
		return (0);
	if (!parse_views_part(&current_pos, views->left))
		return (0);
	if (!parse_views_part(&current_pos, views->right))
		return (0);
	if (*current_pos != '\0')
		return (0);
	return (validate_views_values(views));
}
