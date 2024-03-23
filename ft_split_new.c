/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:43:42 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 09:56:20 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	inside_quotes(char *s, int *i, int *n)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] != quote && s[*i] != 0)
	{
		(*n)++;
		(*i)++;
	}
	if (s[*i] == quote)
		(*n)++;
}

static void	ft_splitstr(char **str, char *s, int num)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	while (j < num)
	{
		n = 0;
		while (ft_isspace(s[i]) == 1 && s[i] != '\0')
			i++;
		while (ft_isspace(s[i]) == 0 && s[i] != '\0')
		{
			n++;
			if (s[i] == '\"' || s[i] == '\'')
				inside_quotes(s, &i, &n);
			i++;
		}
		str[j] = ft_word(s, i - n, i);
		j++;
	}
	str[j] = NULL;
}

char	**ft_split_new(char *s)
{
	char	**str;
	int		num;

	if (!s)
		return (0);
	num = ft_numofstr(s);
	str = (char **)malloc(sizeof(char *) * (num + 1));
	if (!str || !s)
		return (NULL);
	ft_splitstr(str, s, num);
	if (ft_checkmem(str, num) == 0)
		return (NULL);
	return (str);
}
