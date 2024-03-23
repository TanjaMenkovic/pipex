/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:33:28 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 10:38:59 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	inside_quotes(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] != 0)
	{
		if (s[*i] == quote && (s[*i + 1] == ' ' || s[*i + 1] == 0))
			return ;
		(*i)++;
	}
	*i = -1;
}

int	ft_numofstr(char *s)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != 0)
	{
		while (s[i] == ' ' && s[i] != 0)
			i++;
		if (s[i] != 0 && s[i] != ' ')
			n++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			inside_quotes(s, &i);
			if (i == -1)
				return (-1);
			i++;
		}
		else
		{
			while (s[i] != 0 && s[i] != ' ')
				i++;
		}
	}
	return (n);
}

char	*ft_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;
	char	quote;

	i = 0;
	word = malloc(finish - start + 1);
	if (!word)
		return (NULL);
	while (start < finish)
	{
		if (str[start] != '\'' && str[start] != '\"')
			word[i++] = str[start++];
		else
		{
			quote = str[start++];
			while (str[start] != quote && str[start] != '\0')
				word[i++] = str[start++];
			if (str[start] == quote)
				start++;
		}
	}
	word[i] = '\0';
	return (word);
}

int	ft_checkmem(char **str, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (str[i] == 0)
		{
			while (num > 0)
			{
				free(str[num - 1]);
				num--;
			}
			free(str);
			return (0);
		}
		i++;
	}
	return (1);
}
