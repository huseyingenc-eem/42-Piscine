/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:31:56 by bkinali           #+#    #+#             */
/*   Updated: 2025/04/21 02:09:35 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_alpha_numeric(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	new_word;

	i = 0;
	new_word = 1;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		if ((str[i] >= 'a' && str[i] <= 'z') && new_word)
			str[i] -= 32;
		if (is_alpha_numeric(str[i]))
			new_word = 0;
		else
			new_word = 1;
		i++;
	}
	return (str);
}
