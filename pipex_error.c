/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:13:08 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/02/23 12:49:09 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_message(char *s, char *t)
{
	if (!s)
	{
		write(2, "Error: Unknown error\n", 21);
		return (2);
	}
	write(2, "pipex: ", 7);
	if (t)
	{
		write(2, t, ft_strlen(t));
		write(2, ": ", 2);
	}
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	return (2);
}

void	error_msg(char *c, char *str)
{
	write(2, "pipex: ", 7);
	if (c)
		write(2, c, ft_strlen(c));
	if (str)
		write(2, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
