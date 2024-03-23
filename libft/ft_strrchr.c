/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:03:07 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/07 17:11:21 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	char	*cur;
	int		len;

	s = (char *)str;
	len = ft_strlen(s);
	cur = s + len;
	while (*cur != (unsigned char)c)
	{
		if (cur == s)
			return (NULL);
		cur--;
	}
	return (cur);
}
