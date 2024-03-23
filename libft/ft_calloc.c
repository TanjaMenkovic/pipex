/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:01:45 by tmenkovi          #+#    #+#             */
/*   Updated: 2023/11/08 13:17:25 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*el;
	size_t	num;

	num = 0;
	if (nitems != 0 && (4611686014132420608 / nitems) < size)
		return (0);
	num = nitems * size;
	el = malloc(num);
	if (!el)
		return (0);
	ft_bzero(el, num);
	return (el);
}
