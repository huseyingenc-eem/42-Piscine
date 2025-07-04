/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:21:00 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/15 12:25:18 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	first_select;
	int	last_select;

	first_select = 0;
	while (first_select < size - 1)
	{
		last_select = first_select + 1;
		while (last_select < size)
		{
			if (tab[first_select] > tab[last_select])
			{
				ft_swap(&tab[first_select], &tab[last_select]);
			}
			last_select++;
		}
		first_select++;
	}
}
