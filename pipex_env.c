/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:43:42 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 09:59:38 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i] != 0)
	{
		j = 0;
		while (env[i][j] != 0 && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	**env_paths(char **env)
{
	char	**paths;

	paths = NULL;
	if (get_env("PATH", env) != NULL)
		paths = ft_split(get_env("PATH", env), ':');
	return (paths);
}

char	*exec_exists(char *cmd, char *cmd_path)
{
	char	*tmp_path;

	tmp_path = ft_strjoin(cmd_path, cmd);
	if (tmp_path)
	{
		if (access(tmp_path, X_OK | F_OK) == -1)
			free(tmp_path);
		else
			return (tmp_path);
	}
	return (NULL);
}

char	*exec_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	if (ft_isalnum(cmd[0]) == 0)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		cmd_path = exec_exists(cmd, temp);
		free(temp);
		if (cmd_path)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
