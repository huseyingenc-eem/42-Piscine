/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:32:03 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/21 09:34:27 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char			*start;
	unsigned int	i;

	start = dest;
	while (*dest)
		dest++;
	i = 0;
	while (*src && i < nb)
	{
		*dest++ = *src++;
		i++;
	}
	*dest = '\0';
	return (start);
}
