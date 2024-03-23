/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:24:30 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/02/07 12:21:27 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_to_int(char c)
{
	return ((int)(c - '0'));
}

int	ft_atoi(const char *str)
{
	int		minus;
	long	number;

	minus = 1;
	number = 0;
	while (*str != '\0' && ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-' && ft_isdigit(*(str + 1)))
		{
			number = -1 * ft_char_to_int(*(str + 1));
			minus = -1;
			str++;
		}
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str) == 1)
	{
		number = number * 10 + minus * ft_char_to_int(*str);
		if (number / minus < 0)
			return ((minus > 0) * (-1));
		str++;
	}
	return (number);
}
