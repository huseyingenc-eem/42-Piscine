/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgenc <hgenc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 09:35:50 by hgenc             #+#    #+#             */
/*   Updated: 2025/04/21 09:35:51 by hgenc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	char	*temp_str;
	char	*temp_to_find;

	if (!*to_find)
		return (str);
	while (*str)
	{
		if (*str == *to_find)
		{
			temp_str = str;
			temp_to_find = to_find;
			while (*temp_str && *temp_to_find && (*temp_str == *temp_to_find))
			{
				temp_str++;
				temp_to_find++;
			}
			if (*temp_to_find == '\0')
				return (str);
		}
		str++;
	}
	return (0);
}
