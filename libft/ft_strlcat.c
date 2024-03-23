/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:29:32 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/07 11:32:49 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dest == 0 && size == 0)
		return (src_len + size);
	dest_len = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	if (dest_len >= size)
		return (dest_len + src_len);
	i = 0;
	while (i < size - dest_len - 1 && i < src_len)
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (dest_len + src_len);
}
