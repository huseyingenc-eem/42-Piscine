/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:31:10 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/28 16:00:11 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	dividing;

	dividing = 2;
	if (nb < 2)
		return (0);
	while (dividing < nb)
	{
		if (nb % dividing == 0)
			return (0);
		dividing++;
	}
	return (1);
}
