/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:04:08 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/07 12:30:59 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	size_t	i;
	size_t	j;
	char	*s;
	char	*su;

	i = 0;
	s = (char *)str;
	su = (char *)sub;
	if (su[0] == '\0')
		return (s);
	if (n == 0)
		return (0);
	while (s[i] != '\0' && i < n)
	{
		j = 0;
		while (s[i + j] == su[j] && i + j < n
			&& s[i + j] != '\0' && su[j] != '\0')
		{
			if (su[j + 1] == '\0')
				return (s + i);
			j++;
		}
		i++;
	}
	return (0);
}
